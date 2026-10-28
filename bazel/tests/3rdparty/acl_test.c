#include <acl/libacl.h>
#include <stdio.h>
#include <sys/acl.h>

int main(void) {
    acl_t acl = acl_from_mode(0640);
    if (!acl)
        return 1;
    char *text = acl_to_any_text(acl, NULL, ',', 0);
    printf("%s\n", text);
    acl_free(text);
    acl_free(acl);
    return 0;
}
