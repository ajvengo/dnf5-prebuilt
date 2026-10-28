"""Module extension fetching prebuilt dnf5 distributions.

```starlark
bazel_dep(name = "dnf5-prebuilt", version = "...")

dnf5 = use_extension("@dnf5-prebuilt//dnf5-prebuilt:extensions.bzl", "dnf5")
dnf5.toolchains()
use_repo(dnf5, "dnf5_toolchains")

register_toolchains("@dnf5_toolchains//:all")
```

For testing unreleased builds, setting the `DNF5_PREBUILT_DIST_DIR`
environment variable (e.g. `--repo_env=DNF5_PREBUILT_DIST_DIR=/path`) makes the
extension use `dnf5-<version>-<platform>.tar.gz` archives from that directory
instead of the published ones, without integrity checks.
"""

load("//dnf5-prebuilt/private:platforms.bzl", "PLATFORMS")
load("//dnf5-prebuilt/private:repositories.bzl", "dnf5_dist_repository", "dnf5_toolchains_repository")
load("//dnf5-prebuilt/private:versions.bzl", "DEFAULT_VERSION", "RELEASE_URL_TEMPLATE", "VERSIONS")

_toolchains = tag_class(
    doc = "Declares a set of dnf5 toolchains, one per supported platform.",
    attrs = {
        "name": attr.string(
            default = "dnf5",
            doc = "Base name of the generated repositories: `<name>_toolchains` and `<name>_<platform>`.",
        ),
        "version": attr.string(
            default = DEFAULT_VERSION,
            values = VERSIONS.keys(),
            doc = "dnf5 version.",
        ),
    },
)

def _dnf5_extension_impl(mctx):
    local_dir = mctx.getenv("DNF5_PREBUILT_DIST_DIR")
    seen = {}
    for mod in mctx.modules:
        for tag in mod.tags.toolchains:
            if tag.name in seen:
                if seen[tag.name] != tag.version and mod.is_root:
                    fail("dnf5.toolchains(name = %r) is declared with versions %s and %s" %
                         (tag.name, seen[tag.name], tag.version))
                continue
            seen[tag.name] = tag.version
            release = VERSIONS[tag.version]
            dist_repos = {}
            for platform in PLATFORMS:
                repo = "%s_%s" % (tag.name, platform)
                if local_dir:
                    urls = ["file://%s/dnf5-%s-%s.tar.gz" % (local_dir, tag.version, platform)]
                    integrity = ""
                else:
                    urls = [RELEASE_URL_TEMPLATE.format(
                        tag = release["tag"],
                        version = tag.version,
                        platform = platform,
                    )]
                    integrity = release["integrity"].get(platform, "")
                dnf5_dist_repository(
                    name = repo,
                    urls = urls,
                    integrity = integrity,
                    version = tag.version,
                )
                dist_repos[platform] = repo
            dnf5_toolchains_repository(
                name = tag.name + "_toolchains",
                dist_repos = dist_repos,
                platforms = PLATFORMS.keys(),
            )
    return mctx.extension_metadata(reproducible = not local_dir)

dnf5 = module_extension(
    implementation = _dnf5_extension_impl,
    doc = "Fetches prebuilt dnf5 distributions and declares their toolchains.",
    tag_classes = {"toolchains": _toolchains},
    environ = ["DNF5_PREBUILT_DIST_DIR"],
)
