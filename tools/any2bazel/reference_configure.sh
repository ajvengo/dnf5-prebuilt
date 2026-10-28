#!/bin/bash
# Configures the upstream dnf5 CMake build inside a Fedora container and writes
# the CMake File API reply plus a configure trace. Runs as the container's
# entrypoint (see reference.sh); /src is the dnf5 source tree, /build the
# output directory.
set -euo pipefail

dnf -y install cmake gcc-c++ make pkgconf-pkg-config \
    'pkgconfig(fmt)' 'pkgconfig(json-c)' 'pkgconfig(libsolv)' 'pkgconfig(libsolvext)' \
    'pkgconfig(rpm)' 'pkgconfig(libxml-2.0)' 'pkgconfig(glib-2.0)' 'pkgconfig(librepo)' \
    'pkgconfig(sqlite3)' 'pkgconfig(smartcols)' 'cmake(toml11)' libcurl-devel zlib-devel \
    'pkgconfig(sdbus-c++)' 'pkgconfig(libsystemd)' 'pkgconfig(modulemd-2.0)' \
    'pkgconfig(libacl)' 'pkgconfig(libpkgmanifest)' >/tmp/dnf.log 2>&1

rm -rf /build/* /build/.cmake
mkdir -p /build/.cmake/api/v1/query
touch /build/.cmake/api/v1/query/codemodel-v2

# Keep in sync with the header of bazel/dnf5/dnf5.BUILD.bazel.
cmake -S /src -B /build \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=lib64 \
    -DWITH_DNF5DAEMON_CLIENT=OFF -DWITH_DNF5DAEMON_SERVER=OFF \
    -DWITH_PLUGIN_APPSTREAM=OFF -DWITH_PLUGIN_RHSM=OFF -DWITH_PLUGIN_MANIFEST=ON \
    -DWITH_PYTHON_PLUGINS_LOADER=OFF -DWITH_PLUGIN_SYSTEMD_INHIBIT=OFF -DWITH_SYSTEMD=OFF \
    -DWITH_ACL=ON -DWITH_MODULEMD=ON -DWITH_HTML=OFF -DWITH_MAN=OFF -DWITH_TRANSLATIONS=OFF \
    -DWITH_TESTS=OFF -DWITH_PERL5=OFF -DWITH_PYTHON3=OFF -DWITH_RUBY=OFF -DWITH_GO=OFF \
    --trace-expand --trace-format=json-v1 2>/build/trace.jsonl

rpm -q libsolv librepo rpm fmt json-c toml11-devel libxml2 glib2 sqlite util-linux-core \
    libmodulemd libacl libpkgmanifest >/build/versions.txt || true
chown -R "${HOST_UID}:${HOST_GID}" /build
