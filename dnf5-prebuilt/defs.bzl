"""Public API of dnf5-prebuilt."""

load(
    "//dnf5-prebuilt:toolchain.bzl",
    _Dnf5Info = "Dnf5Info",
    _current_dnf5_toolchain = "current_dnf5_toolchain",
    _dnf5_toolchain = "dnf5_toolchain",
)

Dnf5Info = _Dnf5Info
current_dnf5_toolchain = _current_dnf5_toolchain
dnf5_toolchain = _dnf5_toolchain
