#!/usr/bin/env python3
"""Collects the licenses of everything bundled in the dnf5 distribution.

Copies the license files of every third-party component linked into the
binaries built by //bazel/release (C/C++ libraries and the Rust crates of
rpm-sequoia) from Bazel's external repositories into bazel/release/licenses/
and writes bazel/release/licenses/THIRD_PARTY_NOTICES.md.

Run from the repository root after changing dependencies:

    tools/licenses/collect.py

It runs `bazel cquery` for every supported platform to find the linked Rust
crates, so the external repositories must be fetchable.
"""

import json
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(ROOT, "bazel", "release", "licenses")
PLATFORMS = ["linux_amd64", "linux_arm64", "osx_amd64", "osx_arm64"]

# component -> (canonical repository, SPDX expression, homepage, license files
# relative to the repository root). A file entry "path#start..end" extracts the
# lines between the first line matching `start` and the next matching `end`.
COMPONENTS = {
    "dnf5": ("+dnf5_extension+dnf5", "GPL-2.0-or-later AND LGPL-2.1-or-later",
             "https://github.com/rpm-software-management/dnf5",
             ["COPYING.md", "gpl-2.0.txt", "lgpl-2.1.txt"]),
    "rpm": ("rpm+", "GPL-2.0-or-later AND LGPL-2.1-or-later", "https://rpm.org", ["COPYING"]),
    "rpm-sequoia": ("rpm-sequoia+", "LGPL-2.0-or-later",
                    "https://github.com/rpm-software-management/rpm-sequoia", ["LICENSE.txt"]),
    "libsolv": ("libsolv+", "BSD-3-Clause", "https://github.com/openSUSE/libsolv", ["LICENSE.BSD"]),
    "librepo": ("librepo+", "LGPL-2.1-or-later", "https://github.com/rpm-software-management/librepo",
                ["COPYING"]),
    "libmodulemd": ("libmodulemd+", "MIT", "https://github.com/fedora-modularity/libmodulemd", ["COPYING"]),
    "libpkgmanifest": ("libpkgmanifest+", "LGPL-2.1-or-later",
                       "https://github.com/rpm-software-management/libpkgmanifest", ["COPYING.LIB"]),
    "libsmartcols": ("libsmartcols+", "LGPL-2.1-or-later", "https://github.com/util-linux/util-linux",
                     ["libsmartcols/COPYING", "Documentation/licenses/COPYING.LGPL-2.1-or-later"]),
    "libacl": ("libacl+", "LGPL-2.1-or-later", "https://savannah.nongnu.org/projects/acl",
               ["doc/COPYING.LGPL"]),
    "libcap": ("libcap+", "BSD-3-Clause OR GPL-2.0-only", "https://sites.google.com/site/fullycapable/",
               ["License"]),
    "json-c": ("json-c+", "MIT", "https://github.com/json-c/json-c", ["COPYING"]),
    "toml11": ("toml11+", "MIT", "https://github.com/ToruNiina/toml11", ["LICENSE"]),
    "fmt": ("fmt+", "MIT", "https://github.com/fmtlib/fmt", ["LICENSE"]),
    "popt": ("popt+", "MIT", "https://github.com/rpm-software-management/popt", ["COPYING"]),
    "curl": ("curl+", "curl", "https://curl.se", ["COPYING"]),
    "openssl": ("openssl+", "Apache-2.0", "https://www.openssl.org", ["LICENSE.txt"]),
    "glib": ("glib+", "LGPL-2.1-or-later", "https://gitlab.gnome.org/GNOME/glib", ["COPYING"]),
    "libffi": ("libffi+", "MIT", "https://sourceware.org/libffi/", ["LICENSE"]),
    "pcre2": ("pcre2+", "BSD-3-Clause WITH PCRE2-exception", "https://github.com/PCRE2Project/pcre2",
              ["LICENCE.md"]),
    "libxml2": ("libxml2+", "MIT", "https://gitlab.gnome.org/GNOME/libxml2", ["Copyright"]),
    "libyaml": ("libyaml+", "MIT", "https://github.com/yaml/libyaml", ["License"]),
    "yaml-cpp": ("yaml-cpp+", "MIT", "https://github.com/jbeder/yaml-cpp", ["LICENSE"]),
    "sqlite": ("sqlite3+", "blessing", "https://sqlite.org",
               ["sqlite3.h#^\\*\\* 2001.*$..^\\*{20,}"]),
    "lua": ("lua+", "MIT", "https://www.lua.org",
            ["src/lua.h#^\\* Copyright \\(C\\) 1994-..^\\*{20,}/$"]),
    "libmagic": ("libmagic+", "BSD-2-Clause", "https://www.darwinsys.com/file/", ["COPYING"]),
    "zchunk": ("zchunk+", "BSD-2-Clause", "https://github.com/zchunk/zchunk", ["LICENSE"]),
    "zlib": ("zlib+", "Zlib", "https://zlib.net", ["zlib-1.3.2/LICENSE"]),
    "zstd": ("zstd+", "BSD-3-Clause", "https://github.com/facebook/zstd", ["LICENSE"]),
    "xz": ("xz+", "0BSD", "https://tukaani.org/xz/", ["COPYING"]),
    "bzip2": ("bzip2+", "bzip2-1.0.6", "https://sourceware.org/bzip2/", ["LICENSE"]),
    "llvm-runtimes": ("llvm++llvm+llvm-project", "Apache-2.0 WITH LLVM-exception",
                      "https://llvm.org (libc++, libc++abi, libunwind, compiler-rt)",
                      ["libcxx/LICENSE.TXT"]),
}

LICENSE_FILE_RE = re.compile(r"^(LICEN[CS]E|COPYING|COPYRIGHT|UNLICENSE|NOTICE)", re.IGNORECASE)


def bazel(*args):
    return subprocess.run(["bazel", *args], cwd=ROOT, check=True, capture_output=True, text=True).stdout


def extract(path, spec):
    start, end = spec.split("..", 1)
    lines, copying = [], False
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            if not copying and re.search(start, line):
                copying = True
            if copying:
                lines.append(line)
                if len(lines) > 1 and re.search(end, line):
                    break
    if not lines:
        sys.exit("no license text matching %r in %s" % (spec, path))
    return "".join(lines)


def copy_component(external, name, repo, files):
    dest = os.path.join(OUT, name)
    os.makedirs(dest, exist_ok=True)
    for entry in files:
        rel, _, spec = entry.partition("#")
        src = os.path.join(external, repo, rel)
        if spec:
            with open(os.path.join(dest, "LICENSE"), "w") as f:
                f.write(extract(src, spec))
        else:
            shutil.copyfile(src, os.path.join(dest, os.path.basename(rel)))


def rust_crates():
    """(name, version, repo) of the Rust libraries linked into rpm-sequoia."""
    crates = set()
    for platform in PLATFORMS:
        out = bazel("cquery", "kind(rust_library, deps(@rpm-sequoia//:rpm_sequoia_staticlib))",
                    "--config=" + platform, "--output=label")
        for line in out.splitlines():
            m = re.match(r"@@([^/]*rpm_sequoia_crates__([A-Za-z0-9_-]+?)-(\d[^/]*))//", line)
            if m:
                crates.add((m.group(2), m.group(3), m.group(1)))
    return sorted(crates)


def cargo_license(path):
    with open(path, encoding="utf-8") as f:
        m = re.search(r'^license\s*=\s*"([^"]+)"', f.read(), re.MULTILINE)
    return m.group(1) if m else "see license files"


def main():
    external = os.path.join(bazel("info", "output_base").strip(), "external")
    if os.path.isdir(OUT):
        shutil.rmtree(OUT)
    os.makedirs(OUT)

    rows = []
    for name, (repo, spdx, homepage, files) in sorted(COMPONENTS.items()):
        copy_component(external, name, repo, files)
        rows.append((name, spdx, homepage))

    crate_rows = []
    for crate, version, repo in rust_crates():
        src = os.path.join(external, repo)
        dest = os.path.join(OUT, "rust", "%s-%s" % (crate, version))
        os.makedirs(dest)
        found = [f for f in sorted(os.listdir(src)) if LICENSE_FILE_RE.match(f) and
                 os.path.isfile(os.path.join(src, f))]
        for f in found:
            shutil.copyfile(os.path.join(src, f), os.path.join(dest, f))
        crate_rows.append((crate, version, cargo_license(os.path.join(src, "Cargo.toml")), len(found)))

    with open(os.path.join(OUT, "THIRD_PARTY_NOTICES.md"), "w") as f:
        f.write("# Third-party notices\n\n")
        f.write("The dnf5 distribution built by dnf5-prebuilt contains the following\n"
                "software. Their license texts are in the directory of the same name\n"
                "next to this file. Corresponding sources: the upstream releases\n"
                "referenced by bazel/extensions.bzl, MODULE.bazel and\n"
                "bazel/3rdparty/modules/*/*/source.json, plus the patches in this\n"
                "repository.\n\n")
        f.write("| Component | License | Homepage |\n|---|---|---|\n")
        for name, spdx, homepage in rows:
            f.write("| %s | %s | %s |\n" % (name, spdx, homepage))
        f.write("\n## Rust crates (statically linked into rpm-sequoia)\n\n")
        f.write("License texts are in rust/<crate>-<version>/.\n\n")
        f.write("| Crate | Version | License |\n|---|---|---|\n")
        for crate, version, lic, n in crate_rows:
            f.write("| %s | %s | %s%s |\n" % (crate, version, lic, "" if n else " (no license file shipped by the crate)"))
    print("collected %d components and %d crates into %s" % (len(rows), len(crate_rows), OUT))


if __name__ == "__main__":
    main()
