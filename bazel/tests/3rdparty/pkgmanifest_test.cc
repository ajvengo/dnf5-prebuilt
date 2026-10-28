// Link/run smoke test for libpkgmanifest: serialize and re-parse a manifest.
#include <libpkgmanifest/manifest/manifest.hpp>
#include <libpkgmanifest/manifest/parser.hpp>
#include <libpkgmanifest/manifest/serializer.hpp>

#include <cstdio>
#include <filesystem>
#include <string>

int main() {
    libpkgmanifest::manifest::Manifest manifest;
    auto path = (std::filesystem::temp_directory_path() / "dnf5-bazel-manifest.yaml").string();
    libpkgmanifest::manifest::Serializer().serialize(manifest, path);
    auto parsed = libpkgmanifest::manifest::Parser().parse(path);
    std::printf("libpkgmanifest: document %s, version %u.%u.%u\n",
                parsed.get_document().c_str(),
                parsed.get_version().get_major(),
                parsed.get_version().get_minor(),
                parsed.get_version().get_patch());
    std::filesystem::remove(path);
    return parsed.get_document().empty() ? 1 : 0;
}
