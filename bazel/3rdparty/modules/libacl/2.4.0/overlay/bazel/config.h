/* config.h for libacl 2.4.0 (Linux only).
 *
 * From `./configure --disable-nls` against glibc 2.28, adjusted for the
 * hermetic toolchain's Linux 4.19 UAPI headers: <linux/openat2.h> (5.6+) is
 * not available, so the openat2-based safe restore path is disabled.
 */

#define EXPORT __attribute__ ((visibility ("default"))) extern
#define HAVE_DLFCN_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_UNISTD_H 1
#define HAVE_VISIBILITY_ATTRIBUTE /**/
#define HAVE_WCHAR_H 1
#define PACKAGE "acl"
#define PACKAGE_BUGREPORT "acl-devel@nongnu.org"
#define PACKAGE_NAME "acl"
#define PACKAGE_STRING "acl 2.4.0"
#define PACKAGE_TARNAME "acl"
#define PACKAGE_URL ""
#define PACKAGE_VERSION "2.4.0"
#define STDC_HEADERS 1
#define VERSION "2.4.0"

#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
