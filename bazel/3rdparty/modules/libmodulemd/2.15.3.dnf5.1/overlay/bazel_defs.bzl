"""Helpers for the libmodulemd Bazel overlay."""

# Execroot-relative path of this repository ("" when it is the main repo).
REPO_ROOT = Label("//:BUILD.bazel").workspace_root

def repo_path(path):
    """Returns `path` (relative to this repository) relative to the execroot."""
    return REPO_ROOT + "/" + path if REPO_ROOT else path
