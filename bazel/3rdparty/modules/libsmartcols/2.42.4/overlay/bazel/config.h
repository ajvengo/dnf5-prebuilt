/* config.h for building libsmartcols (and the bits of util-linux libcommon it
 * needs) without running util-linux's configure.
 *
 * Only the macros referenced by libsmartcols/src, the libcommon files listed
 * in BUILD.bazel and the headers they include are kept. Linux values come
 * from `./configure --disable-all-programs --enable-libsmartcols` against
 * glibc 2.28; macOS overrides follow.
 */
#ifndef UL_BAZEL_CONFIG_H
#define UL_BAZEL_CONFIG_H

/* AC_USE_SYSTEM_EXTENSIONS */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif

#define PACKAGE "util-linux"
#define PACKAGE_NAME "util-linux"
#define PACKAGE_VERSION "2.42.4"
#define PACKAGE_STRING "util-linux 2.42.4"
#define PACKAGE_BUGREPORT "kzak@redhat.com"
#define VERSION "2.42.4"
#define STDC_HEADERS 1

#define HAVE_DIRFD 1
#define HAVE_ERR 1
#define HAVE_ERRX 1
#define HAVE_ERR_H 1
#define HAVE_ERRNO_H 1
#define HAVE_FCNTL_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_LANGINFO_H 1
#define HAVE_LOCALE_H 1
#define HAVE_NANOSLEEP 1
#define HAVE_OPEN_MEMSTREAM 1
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_STRNDUP 1
#define HAVE_STRNLEN 1
#define HAVE_SYS_IOCTL_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TTYDEFAULTS_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_TLS 1
#define HAVE_UNISTD_H 1
#define HAVE_USLEEP 1
#define HAVE_WARN 1
#define HAVE_WARNX 1
#define HAVE_WCHAR_H 1
#define HAVE_WIDECHAR 1

#if defined(__linux__)
#define HAVE_GETAUXVAL 1
#define HAVE_GETTTYNAM 1
#define HAVE_LANGINFO_ALTMON 1
#define HAVE_LANGINFO_NL_ABALTMON 1
#define HAVE_LOFF_T 1
#define HAVE_MEMPCPY 1
#define HAVE_PROGRAM_INVOCATION_SHORT_NAME 1
#define HAVE_REALLOCARRAY 1
#define HAVE_RPMATCH 1
#define HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC 1
#define HAVE_SYS_AUXV_H 1
#define HAVE_SYS_SYSMACROS_H 1
#define HAVE___PROGNAME 1
#endif

#if defined(__APPLE__)
#define _DARWIN_C_SOURCE 1
#endif

#endif /* UL_BAZEL_CONFIG_H */
