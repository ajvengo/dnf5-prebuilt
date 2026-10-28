#!/usr/bin/env bash
# Checks the output of the genrule that ran dnf5 through $(DNF5).
set -euo pipefail
grep -q "^dnf5 version " "$VERSION_FILE"
