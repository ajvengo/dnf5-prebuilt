# Third-party notices

The dnf5 distribution built by dnf5-prebuilt contains the following
software. Their license texts are in the directory of the same name
next to this file. Corresponding sources: the upstream releases
referenced by bazel/extensions.bzl, MODULE.bazel and
bazel/3rdparty/modules/*/*/source.json, plus the patches in this
repository.

| Component | License | Homepage |
|---|---|---|
| bzip2 | bzip2-1.0.6 | https://sourceware.org/bzip2/ |
| curl | curl | https://curl.se |
| dnf5 | GPL-2.0-or-later AND LGPL-2.1-or-later | https://github.com/rpm-software-management/dnf5 |
| fmt | MIT | https://github.com/fmtlib/fmt |
| glib | LGPL-2.1-or-later | https://gitlab.gnome.org/GNOME/glib |
| json-c | MIT | https://github.com/json-c/json-c |
| libacl | LGPL-2.1-or-later | https://savannah.nongnu.org/projects/acl |
| libcap | BSD-3-Clause OR GPL-2.0-only | https://sites.google.com/site/fullycapable/ |
| libffi | MIT | https://sourceware.org/libffi/ |
| libmagic | BSD-2-Clause | https://www.darwinsys.com/file/ |
| libmodulemd | MIT | https://github.com/fedora-modularity/libmodulemd |
| libpkgmanifest | LGPL-2.1-or-later | https://github.com/rpm-software-management/libpkgmanifest |
| librepo | LGPL-2.1-or-later | https://github.com/rpm-software-management/librepo |
| libsmartcols | LGPL-2.1-or-later | https://github.com/util-linux/util-linux |
| libsolv | BSD-3-Clause | https://github.com/openSUSE/libsolv |
| libxml2 | MIT | https://gitlab.gnome.org/GNOME/libxml2 |
| libyaml | MIT | https://github.com/yaml/libyaml |
| llvm-runtimes | Apache-2.0 WITH LLVM-exception | https://llvm.org (libc++, libc++abi, libunwind, compiler-rt) |
| lua | MIT | https://www.lua.org |
| openssl | Apache-2.0 | https://www.openssl.org |
| pcre2 | BSD-3-Clause WITH PCRE2-exception | https://github.com/PCRE2Project/pcre2 |
| popt | MIT | https://github.com/rpm-software-management/popt |
| rpm | GPL-2.0-or-later AND LGPL-2.1-or-later | https://rpm.org |
| rpm-sequoia | LGPL-2.0-or-later | https://github.com/rpm-software-management/rpm-sequoia |
| sqlite | blessing | https://sqlite.org |
| toml11 | MIT | https://github.com/ToruNiina/toml11 |
| xz | 0BSD | https://tukaani.org/xz/ |
| yaml-cpp | MIT | https://github.com/jbeder/yaml-cpp |
| zchunk | BSD-2-Clause | https://github.com/zchunk/zchunk |
| zlib | Zlib | https://zlib.net |
| zstd | BSD-3-Clause | https://github.com/facebook/zstd |

## Rust crates (statically linked into rpm-sequoia)

License texts are in rust/<crate>-<version>/.

| Crate | Version | License |
|---|---|---|
| aead | 0.5.2 | MIT OR Apache-2.0 |
| aes | 0.8.4 | MIT OR Apache-2.0 |
| aes-gcm | 0.10.3 | Apache-2.0 OR MIT |
| aho-corasick | 1.1.5 | Unlicense OR MIT |
| anyhow | 1.0.104 | MIT OR Apache-2.0 |
| argon2 | 0.5.3 | MIT OR Apache-2.0 |
| ascii-canvas | 4.0.0 | Apache-2.0/MIT |
| autocfg | 1.5.1 | Apache-2.0 OR MIT |
| base16ct | 0.2.0 | Apache-2.0 OR MIT |
| base64 | 0.22.1 | MIT OR Apache-2.0 |
| base64ct | 1.8.3 | Apache-2.0 OR MIT |
| bit-set | 0.8.0 | Apache-2.0 OR MIT |
| bit-vec | 0.8.0 | Apache-2.0 OR MIT |
| bitvec | 1.1.1 | MIT |
| blake2 | 0.10.6 | MIT OR Apache-2.0 |
| block-buffer | 0.10.4 | MIT OR Apache-2.0 |
| block-buffer | 0.12.1 | MIT OR Apache-2.0 |
| block-padding | 0.3.3 | MIT OR Apache-2.0 |
| blowfish | 0.9.1 | MIT OR Apache-2.0 |
| buffered-reader | 1.4.1 | LGPL-2.0-or-later |
| byteorder | 1.5.0 | Unlicense OR MIT |
| camellia | 0.1.0 | MIT OR Apache-2.0 |
| cast5 | 0.11.1 | MIT OR Apache-2.0 |
| cbc | 0.1.2 | MIT OR Apache-2.0 |
| cfb-mode | 0.8.2 | MIT OR Apache-2.0 |
| cfg-if | 1.0.4 | MIT OR Apache-2.0 |
| chrono | 0.4.45 | MIT OR Apache-2.0 |
| cipher | 0.4.4 | MIT OR Apache-2.0 |
| cmac | 0.7.2 | MIT OR Apache-2.0 |
| cmov | 0.5.4 | Apache-2.0 OR MIT |
| const-oid | 0.9.6 | Apache-2.0 OR MIT |
| core-foundation-sys | 0.8.7 | MIT OR Apache-2.0 |
| cpufeatures | 0.2.17 | MIT OR Apache-2.0 |
| cpufeatures | 0.3.1 | MIT OR Apache-2.0 |
| crypto-bigint | 0.5.5 | Apache-2.0 OR MIT |
| crypto-common | 0.1.7 | MIT OR Apache-2.0 |
| crypto-common | 0.2.2 | MIT OR Apache-2.0 |
| ctr | 0.9.2 | MIT OR Apache-2.0 |
| ctutils | 0.4.2 | Apache-2.0 OR MIT |
| curve25519-dalek | 4.1.3 | BSD-3-Clause |
| cx448 | 0.1.1 | BSD-3-Clause (no license file shipped by the crate) |
| dbl | 0.3.2 | MIT OR Apache-2.0 |
| der | 0.7.10 | Apache-2.0 OR MIT |
| des | 0.8.1 | MIT OR Apache-2.0 |
| digest | 0.10.7 | MIT OR Apache-2.0 |
| digest | 0.11.3 | MIT OR Apache-2.0 |
| dsa | 0.6.3 | Apache-2.0 OR MIT |
| dyn-clone | 1.0.20 | MIT OR Apache-2.0 |
| eax | 0.5.0 | Apache-2.0 OR MIT |
| ecb | 0.1.2 | MIT |
| ecdsa | 0.16.9 | Apache-2.0 OR MIT |
| ed25519 | 2.2.3 | Apache-2.0 OR MIT |
| ed25519-dalek | 2.2.0 | BSD-3-Clause |
| either | 1.18.0 | MIT OR Apache-2.0 |
| elliptic-curve | 0.13.8 | Apache-2.0 OR MIT |
| ena | 0.14.4 | MIT OR Apache-2.0 |
| equivalent | 1.0.2 | Apache-2.0 OR MIT |
| ff | 0.13.1 | MIT/Apache-2.0 |
| fixedbitset | 0.5.7 | MIT OR Apache-2.0 |
| funty | 2.0.0 | MIT |
| generic-array | 0.14.7 | MIT |
| generic-array | 1.4.5 | MIT |
| getrandom | 0.2.17 | MIT OR Apache-2.0 |
| getrandom | 0.3.4 | MIT OR Apache-2.0 |
| ghash | 0.5.1 | Apache-2.0 OR MIT |
| group | 0.13.0 | MIT/Apache-2.0 |
| hashbrown | 0.17.1 | MIT OR Apache-2.0 |
| hkdf | 0.12.4 | MIT OR Apache-2.0 |
| hmac | 0.12.1 | MIT OR Apache-2.0 |
| hybrid-array | 0.3.1 | MIT OR Apache-2.0 |
| hybrid-array | 0.4.14 | MIT OR Apache-2.0 |
| iana-time-zone | 0.1.65 | MIT OR Apache-2.0 |
| icu_collections | 2.1.1 | Unicode-3.0 |
| icu_locale_core | 2.1.1 | Unicode-3.0 |
| icu_normalizer | 2.1.1 | Unicode-3.0 |
| icu_normalizer_data | 2.1.1 | Unicode-3.0 |
| icu_properties | 2.1.2 | Unicode-3.0 |
| icu_properties_data | 2.1.2 | Unicode-3.0 |
| icu_provider | 2.1.1 | Unicode-3.0 |
| idea | 0.5.1 | MIT OR Apache-2.0 |
| idna | 1.1.0 | MIT OR Apache-2.0 |
| idna_adapter | 1.2.1 | Apache-2.0 OR MIT |
| indexmap | 2.14.2 | Apache-2.0 OR MIT |
| inout | 0.1.4 | MIT OR Apache-2.0 |
| itertools | 0.14.0 | MIT OR Apache-2.0 |
| itoa | 1.0.18 | MIT OR Apache-2.0 |
| keccak | 0.1.6 | Apache-2.0 OR MIT |
| keccak | 0.2.2 | Apache-2.0 OR MIT |
| kem | 0.3.0 | Apache-2.0 OR MIT |
| lalrpop | 0.22.2 | Apache-2.0 OR MIT |
| lalrpop-util | 0.22.2 | Apache-2.0 OR MIT |
| lazy_static | 1.5.0 | MIT OR Apache-2.0 |
| libc | 0.2.189 | MIT OR Apache-2.0 |
| libm | 0.2.16 | MIT |
| litemap | 0.8.3 | Unicode-3.0 |
| lock_api | 0.4.14 | MIT OR Apache-2.0 |
| log | 0.4.34 | MIT OR Apache-2.0 |
| md | 5-0.10.6 | MIT OR Apache-2.0 |
| memchr | 2.8.3 | Unlicense OR MIT |
| memsec | 0.7.0 | MIT |
| ml-dsa | 0.1.1 | Apache-2.0 OR MIT |
| ml-kem | 0.3.2 | Apache-2.0 OR MIT |
| module-lattice | 0.2.3 | Apache-2.0 OR MIT |
| new_debug_unreachable | 1.0.6 | MIT |
| num-bigint-dig | 0.8.6 | MIT/Apache-2.0 |
| num-integer | 0.1.47 | MIT OR Apache-2.0 |
| num-iter | 0.1.46 | MIT OR Apache-2.0 |
| num-traits | 0.2.19 | MIT OR Apache-2.0 |
| ocb3 | 0.1.0 | Apache-2.0 OR MIT |
| opaque-debug | 0.3.1 | MIT OR Apache-2.0 |
| p256 | 0.13.2 | Apache-2.0 OR MIT |
| p384 | 0.13.1 | Apache-2.0 OR MIT |
| p521 | 0.13.3 | Apache-2.0 OR MIT |
| parking_lot | 0.12.5 | MIT OR Apache-2.0 |
| parking_lot_core | 0.9.12 | MIT OR Apache-2.0 |
| password-hash | 0.5.0 | MIT OR Apache-2.0 |
| pem-rfc7468 | 0.7.0 | Apache-2.0 OR MIT |
| petgraph | 0.7.1 | MIT OR Apache-2.0 |
| phf_shared | 0.11.3 | MIT |
| pkcs1 | 0.7.5 | Apache-2.0 OR MIT |
| pkcs8 | 0.10.2 | Apache-2.0 OR MIT |
| polyval | 0.6.2 | Apache-2.0 OR MIT |
| potential_utf | 0.1.6 | Unicode-3.0 |
| ppv-lite86 | 0.2.21 | MIT OR Apache-2.0 |
| precomputed-hash | 0.1.1 | MIT |
| primeorder | 0.13.6 | Apache-2.0 OR MIT |
| proc-macro2 | 1.0.107 | MIT OR Apache-2.0 |
| quote | 1.0.47 | MIT OR Apache-2.0 |
| radium | 0.7.0 | MIT |
| rand | 0.8.8 | MIT OR Apache-2.0 |
| rand | 0.9.5 | MIT OR Apache-2.0 |
| rand_chacha | 0.3.1 | MIT OR Apache-2.0 |
| rand_core | 0.10.1 | MIT OR Apache-2.0 |
| rand_core | 0.6.4 | MIT OR Apache-2.0 |
| rand_core | 0.9.5 | MIT OR Apache-2.0 |
| regex | 1.13.1 | MIT OR Apache-2.0 |
| regex-automata | 0.4.18 | MIT OR Apache-2.0 |
| regex-syntax | 0.8.11 | MIT OR Apache-2.0 |
| rfc6979 | 0.4.0 | Apache-2.0 OR MIT |
| ripemd | 0.1.3 | MIT OR Apache-2.0 |
| rsa | 0.9.10 | MIT OR Apache-2.0 |
| rustc_version | 0.4.1 | MIT OR Apache-2.0 |
| same-file | 1.0.6 | Unlicense/MIT |
| scopeguard | 1.2.0 | MIT OR Apache-2.0 |
| sec1 | 0.7.3 | Apache-2.0 OR MIT |
| semver | 1.0.28 | MIT OR Apache-2.0 |
| sequoia-openpgp | 2.4.1 | LGPL-2.0-or-later |
| sequoia-policy-config | 0.8.2 | LGPL-2.0-or-later |
| serde | 1.0.229 | MIT OR Apache-2.0 |
| serde_core | 1.0.229 | MIT OR Apache-2.0 |
| serde_json | 1.0.151 | MIT OR Apache-2.0 |
| serde_spanned | 1.1.1 | MIT OR Apache-2.0 |
| serdect | 0.2.0 | Apache-2.0 OR MIT |
| sha1collisiondetection | 0.3.4 | MIT |
| sha2 | 0.10.9 | MIT OR Apache-2.0 |
| sha3 | 0.10.9 | MIT OR Apache-2.0 |
| sha3 | 0.11.0 | MIT OR Apache-2.0 |
| shake | 0.1.0 | MIT OR Apache-2.0 |
| signature | 2.2.0 | Apache-2.0 OR MIT |
| signature | 3.0.0 | Apache-2.0 OR MIT |
| siphasher | 1.0.3 | MIT/Apache-2.0 |
| slh-dsa | 0.0.3 | Apache-2.0 OR MIT |
| smallvec | 1.16.0 | MIT OR Apache-2.0 |
| spin | 0.9.9 | MIT |
| spki | 0.7.3 | Apache-2.0 OR MIT |
| sponge-cursor | 0.1.0 | MIT OR Apache-2.0 |
| stable_deref_trait | 1.2.1 | MIT OR Apache-2.0 |
| string_cache | 0.8.9 | MIT OR Apache-2.0 |
| subtle | 2.6.1 | BSD-3-Clause |
| syn | 2.0.119 | MIT OR Apache-2.0 |
| syn | 3.0.5 | MIT OR Apache-2.0 |
| synstructure | 0.13.2 | MIT |
| tap | 1.0.1 | MIT |
| term | 1.2.1 | MIT OR Apache-2.0 |
| thiserror | 2.0.20 | MIT OR Apache-2.0 |
| tinystr | 0.8.4 | Unicode-3.0 |
| toml | 1.1.5-spec-1.1.0 | MIT OR Apache-2.0 |
| toml_datetime | 1.1.1-spec-1.1.0 | MIT OR Apache-2.0 |
| toml_parser | 1.1.3-spec-1.1.0 | MIT OR Apache-2.0 |
| toml_writer | 1.1.2-spec-1.1.0 | MIT OR Apache-2.0 |
| twofish | 0.7.1 | MIT OR Apache-2.0 |
| typenum | 1.20.1 | MIT OR Apache-2.0 |
| unicode-ident | 1.0.24 | (MIT OR Apache-2.0) AND Unicode-3.0 |
| unicode-xid | 0.2.6 | MIT OR Apache-2.0 |
| universal-hash | 0.5.1 | MIT OR Apache-2.0 |
| utf8_iter | 1.0.4 | Apache-2.0 OR MIT |
| version_check | 0.9.5 | MIT/Apache-2.0 |
| walkdir | 2.5.0 | Unlicense/MIT |
| winnow | 1.0.4 | MIT |
| writeable | 0.6.4 | Unicode-3.0 |
| wyz | 0.5.1 | MIT |
| x25519-dalek | 2.0.1 | BSD-3-Clause |
| xxhash-rust | 0.8.18 | BSL-1.0 |
| yoke | 0.8.3 | Unicode-3.0 |
| zerocopy | 0.7.35 | BSD-2-Clause OR Apache-2.0 OR MIT |
| zerocopy | 0.8.56 | BSD-2-Clause OR Apache-2.0 OR MIT |
| zerofrom | 0.1.8 | Unicode-3.0 |
| zeroize | 1.9.0 | Apache-2.0 OR MIT |
| zerotrie | 0.2.5 | Unicode-3.0 |
| zerovec | 0.11.8 | Unicode-3.0 |
| zmij | 1.0.23 | MIT |
