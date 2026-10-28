/* Link/run smoke test for librepo (curl, glib, libxml2, zchunk, librpm). */
#include <librepo/librepo.h>
#include <stdio.h>

int main(void) {
    GError *err = NULL;
    LrHandle *h = lr_handle_init();
    if (!h)
        return 1;
    char *urls[] = {"file:///nonexistent", NULL};
    if (!lr_handle_setopt(h, &err, LRO_URLS, urls))
        return 2;
    if (!lr_handle_setopt(h, &err, LRO_REPOTYPE, LR_YUMREPO))
        return 3;
    LrYumRepoMd *repomd = lr_yum_repomd_init();
    lr_yum_repomd_free(repomd);
    lr_handle_free(h);
    printf("librepo %s ok\n", LR_VERSION);
    return 0;
}
