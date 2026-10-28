/*
 * Minimal <libintl.h> for platforms whose C library has no gettext (macOS).
 *
 * dnf5 is built without translations (WITH_TRANSLATIONS=OFF), so every lookup
 * returns the untranslated message, exactly like glibc does when no message
 * catalog is installed.
 */
#ifndef DNF5_PREBUILT_COMPAT_LIBINTL_H
#define DNF5_PREBUILT_COMPAT_LIBINTL_H

#ifdef __cplusplus
extern "C" {
#endif

static inline char * gettext(const char * msgid) {
    return (char *)msgid;
}

static inline char * dgettext(const char * domainname, const char * msgid) {
    (void)domainname;
    return (char *)msgid;
}

static inline char * dcgettext(const char * domainname, const char * msgid, int category) {
    (void)domainname;
    (void)category;
    return (char *)msgid;
}

static inline char * ngettext(const char * msgid, const char * msgid_plural, unsigned long int n) {
    return (char *)(n == 1 ? msgid : msgid_plural);
}

static inline char * dngettext(
    const char * domainname, const char * msgid, const char * msgid_plural, unsigned long int n) {
    (void)domainname;
    return (char *)(n == 1 ? msgid : msgid_plural);
}

static inline char * textdomain(const char * domainname) {
    return (char *)(domainname ? domainname : "messages");
}

static inline char * bindtextdomain(const char * domainname, const char * dirname) {
    (void)domainname;
    return (char *)dirname;
}

static inline char * bind_textdomain_codeset(const char * domainname, const char * codeset) {
    (void)domainname;
    return (char *)codeset;
}

#ifdef __cplusplus
}
#endif

#endif /* DNF5_PREBUILT_COMPAT_LIBINTL_H */
