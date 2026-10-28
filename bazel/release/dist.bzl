"""Assembles the relocatable dnf5 distribution (private API).

`dist_mtree` writes a BSD mtree specification placing the outputs of a set of
targets at chosen directories of the distribution; tar.bzl's `tar_rule` turns
it into a reproducible archive.
"""

load("@tar.bzl//tar:tar.bzl", "tar_rule")

def _is_shared_object(basename):
    return basename.endswith((".so", ".dylib")) or ".so." in basename

def _common_dir(paths):
    """Longest common directory of a list of '/'-separated paths."""
    parts = [p.split("/")[:-1] for p in paths]
    common = parts[0]
    for p in parts[1:]:
        n = 0
        for a, b in zip(common, p):
            if a != b:
                break
            n += 1
        common = common[:n]
    return "/".join(common)

def _dist_mtree_impl(ctx):
    entries = {}  # path in archive -> (file, mode)
    for target, dest in ctx.attr.srcs.items():
        files = target[DefaultInfo].files.to_list()
        if len(files) == 1:
            relpaths = {files[0]: files[0].basename}
        else:
            # Keep the layout of multi-file targets (e.g. filegroups of a
            # directory tree) relative to their common directory.
            root = _common_dir([f.short_path for f in files])
            relpaths = {f: f.short_path[len(root):].lstrip("/") for f in files}
        for f, rel in relpaths.items():
            if "/" not in rel:
                rel = ctx.attr.renames.get(rel, rel)
            path = "/".join([p for p in [ctx.attr.prefix, dest, rel] if p])
            if path in entries:
                fail("%s is provided by both %s and %s" % (path, entries[path][0], f))
            is_exec = _is_shared_object(f.basename) or f.basename in ctx.attr.executables
            entries[path] = (f, "0755" if is_exec else "0644")

    dirs = {}
    for path in entries:
        segments = path.split("/")[:-1]
        for i in range(1, len(segments) + 1):
            dirs["/".join(segments[:i])] = True

    lines = ["%s uid=0 gid=0 time=0 mode=0755 type=dir" % d for d in sorted(dirs)]
    for path in sorted(entries):
        f, mode = entries[path]
        lines.append("%s uid=0 gid=0 time=0 mode=%s type=file content=%s" % (path, mode, f.path))

    out = ctx.actions.declare_file(ctx.label.name + ".spec")
    ctx.actions.write(out, "\n".join(lines) + "\n")
    return [DefaultInfo(files = depset([out]))]

dist_mtree = rule(
    implementation = _dist_mtree_impl,
    doc = "Writes an mtree spec placing the outputs of `srcs` at the given directories.",
    attrs = {
        "executables": attr.string_list(
            doc = "Basenames (before renaming) installed with mode 0755; shared objects always are.",
        ),
        "prefix": attr.string(doc = "Top-level directory of the archive."),
        "renames": attr.string_dict(
            doc = "Basename -> installed basename, for files installed directly in their destination directory.",
        ),
        "srcs": attr.label_keyed_string_dict(
            allow_files = True,
            doc = "Target -> destination directory. Single files are installed under their basename; " +
                  "multi-file targets keep their layout relative to their common directory.",
        ),
    },
)

def dnf5_distribution(name, srcs, prefix, executables = [], renames = {}, **kwargs):
    """Builds `<name>.tar.gz` with `srcs` laid out under `prefix/`.

    Args:
      name: name of the archive target.
      srcs: dict of target -> destination directory, see `dist_mtree`.
      prefix: top-level directory of the archive.
      executables: basenames installed with mode 0755, see `dist_mtree`.
      renames: basename -> installed basename, see `dist_mtree`.
      **kwargs: common attributes (visibility, tags, target_compatible_with...).
    """
    dist_mtree(
        name = name + "_mtree",
        srcs = srcs,
        prefix = prefix,
        executables = executables,
        renames = renames,
        **kwargs
    )
    tar_rule(
        name = name,
        srcs = srcs.keys(),
        mtree = name + "_mtree",
        compress = "gzip",
        out = name + ".tar.gz",
        **kwargs
    )
