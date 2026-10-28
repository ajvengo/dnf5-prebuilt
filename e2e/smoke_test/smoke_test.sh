#!/usr/bin/env bash
# Runs the dnf5 toolchain: version, plugin loading and an (offline) query in an
# empty installroot.
set -euo pipefail

"$DNF5" --version | tee version.txt
grep -q "^dnf5 version " version.txt
grep -q "^libdnf5 version " version.txt

root=$(mktemp -d)
"$DNF5" -y --installroot="$root" --setopt=reposdir=/dev/null --releasever=44 \
    repoquery --available >query.txt
test ! -s query.txt

# Command plugins are loaded from the distribution (dnf5 --help lists them).
"$DNF5" --help | tee help.txt >/dev/null
grep -q "config-manager" help.txt
grep -q "repoclosure" help.txt
echo "smoke test passed"
