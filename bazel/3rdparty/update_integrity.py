#!/usr/bin/env python3
"""Refresh the integrity fields of a module version in this local registry.

Usage:
    bazel/3rdparty/update_integrity.py <module> <version> [--fetch]

Recomputes the SRI hashes of every file under
`modules/<module>/<version>/overlay/` and `.../patches/` and writes them into
`source.json` (`overlay` and `patches` maps). With `--fetch`, the source
archive `url` is downloaded and its `integrity` refreshed as well.
"""

import base64
import hashlib
import json
import os
import sys
import urllib.request

ROOT = os.path.dirname(os.path.abspath(__file__))


def sri(data: bytes) -> str:
    return "sha256-" + base64.b64encode(hashlib.sha256(data).digest()).decode()


def files_under(base: str):
    for dirpath, _, filenames in os.walk(base):
        for name in sorted(filenames):
            path = os.path.join(dirpath, name)
            yield os.path.relpath(path, base), path


def main(argv):
    if len(argv) < 3:
        sys.exit(__doc__)
    module, version = argv[1], argv[2]
    vdir = os.path.join(ROOT, "modules", module, version)
    source_path = os.path.join(vdir, "source.json")
    with open(source_path) as f:
        source = json.load(f)

    if "--fetch" in argv:
        with urllib.request.urlopen(source["url"]) as resp:
            source["integrity"] = sri(resp.read())

    for key in ("overlay", "patches"):
        base = os.path.join(vdir, key)
        if os.path.isdir(base):
            source[key] = {
                rel: sri(open(path, "rb").read())
                for rel, path in sorted(files_under(base))
            }
        else:
            source.pop(key, None)
    if "patches" in source:
        source.setdefault("patch_strip", 1)
    else:
        source.pop("patch_strip", None)

    with open(source_path, "w") as f:
        json.dump(source, f, indent=4, sort_keys=True)
        f.write("\n")


if __name__ == "__main__":
    main(sys.argv)
