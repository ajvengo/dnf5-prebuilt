// Link/run smoke test for librpm, librpmio (incl. rpm-sequoia) and librpmbuild.
#include <rpm/rpmbuild.h>
#include <rpm/rpmlib.h>
#include <rpm/rpmmacro.h>
#include <rpm/rpmpgp.h>
#include <rpm/rpmver.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    if (rpmvercmp("1.0", "1.1") >= 0)
        return 1;
    rpmver v = rpmverParse("2:1.2.3-4.fc44");
    if (!v || std::strcmp(rpmverV(v), "1.2.3") != 0)
        return 2;
    rpmverFree(v);

    rpmPushMacro(nullptr, "dnf5_bazel_test", nullptr, "ok", RMIL_GLOBAL);
    char *expanded = rpmExpand("%{dnf5_bazel_test}", nullptr);
    if (std::strcmp(expanded, "ok") != 0)
        return 3;
    std::free(expanded);

    // Exercises rpm-sequoia: armor some bytes.
    const unsigned char data[] = {0x01, 0x02, 0x03};
    char *armored = pgpArmorWrap(PGPARMOR_PUBKEY, data, sizeof(data));
    if (!armored || std::strstr(armored, "BEGIN PGP PUBLIC KEY BLOCK") == nullptr)
        return 4;
    std::free(armored);

    // librpmbuild symbol, not called: parsing needs a full rpm configuration.
    volatile auto parse = &rpmSpecParse;
    (void)parse;

    std::printf("rpm %s ok\n", RPMVERSION);
    return 0;
}
