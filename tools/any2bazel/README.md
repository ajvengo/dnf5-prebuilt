# any2bazel parity check

The Bazel build of dnf5 (`@dnf5`, overlay in `bazel/dnf5/dnf5.BUILD.bazel`) is
verified against the upstream CMake build with the
any2bazel action-graph differ: every
translation unit must be compiled with equivalent defines, flags and include
roots, and executables must link with equivalent flags. Accepted differences
and their rationale are recorded in `/any2bazel.json`.

| File | Purpose |
|------|---------|
| `reference.sh` | Configures upstream dnf5 with CMake in a Fedora container (`reference_configure.sh`) and extracts `model.cmake.json`. Needs docker. |
| `bazel_model.sh` | Runs `bazel aquery` for `@dnf5//...` (Linux x86_64, `-c opt`), extracts the Bazel model and diffs it against the reference. |
| `model.cmake.json` | Checked-in reference model for dnf5 5.4.6.0, so the diff can be re-run without docker. |
| `reference-versions.txt` | Versions of the system libraries the reference was configured against. |

```sh
work=$(mktemp -d)
cp tools/any2bazel/model.cmake.json "$work/"   # or: tools/any2bazel/reference.sh "$work"
tools/any2bazel/bazel_model.sh "$work"         # prints "CONVERGED errors=0 ..."
```

Both scripts use the any2bazel scripts from `$ANY2BAZEL_SCRIPTS`
(default `~/.agents/skills/any2bazel/scripts`).
