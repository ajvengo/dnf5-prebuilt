/* config.h for json-c 0.19.
 *
 * Linux values come from running CMake against glibc 2.28 (the oldest glibc
 * targeted by this repository), so no newer-glibc-only symbols (e.g.
 * arc4random) are enabled. macOS differences are applied below.
 */

#define HAVE_DLFCN_H
#define HAVE_FCNTL_H
#define HAVE_INTTYPES_H
#define HAVE_LIMITS_H
#define HAVE_LOCALE_H
#define HAVE_MEMORY_H
#define HAVE_STDARG_H
#define HAVE_STDINT_H
#define HAVE_STDLIB_H
#define HAVE_STRINGS_H
#define HAVE_STRING_H
#define HAVE_SYSLOG_H 1
#define HAVE_SYS_CDEFS_H
#define HAVE_SYS_PARAM_H 1
#define HAVE_SYS_RESOURCE_H
#define HAVE_SYS_STAT_H
#define HAVE_SYS_TYPES_H 1
#define HAVE_UNISTD_H 1
#define HAVE_ATOMIC_BUILTINS
#define HAVE_DECL_INFINITY
#define HAVE_DECL_ISINF
#define HAVE_DECL_ISNAN
#define HAVE_DECL_NAN
#define HAVE_OPEN
#define HAVE_REALLOC
#define HAVE_SETLOCALE
#define HAVE_SNPRINTF
#define HAVE_STRCASECMP 1
#define HAVE_STRDUP
#define HAVE_STRERROR
#define HAVE_STRNCASECMP 1
#define HAVE_USELOCALE
#define HAVE_DUPLOCALE
#define HAVE_VASPRINTF
#define HAVE_VPRINTF
#define HAVE_VSNPRINTF
#define HAVE_VSYSLOG 1
#define HAVE_GETRUSAGE
#define HAVE_STRTOLL
#define HAVE_STRTOULL
#define HAVE___THREAD

#if defined(__APPLE__)
#define HAVE_XLOCALE_H
#define HAVE_ARC4RANDOM
#else
#define HAVE_ENDIAN_H
#define HAVE_SYS_RANDOM_H
#define HAVE_GETRANDOM
#endif

#define JSON_C_HAVE_INTTYPES_H 1

#define PACKAGE "json-c"
#define PACKAGE_BUGREPORT "json-c@googlegroups.com"
#define PACKAGE_NAME "json-c"
#define PACKAGE_STRING "json-c 0.19"
#define PACKAGE_TARNAME "json-c"
#define PACKAGE_URL "https://github.com/json-c/json-c"
#define PACKAGE_VERSION "0.19"
#define VERSION "0.19"

/* All supported targets are LP64. */
#define SIZEOF_INT 4
#define SIZEOF_INT64_T 8
#define SIZEOF_LONG 8
#define SIZEOF_LONG_LONG 8
#define SIZEOF_SIZE_T 8
#define SIZEOF_SSIZE_T 8
#define SPEC___THREAD __thread
#define STDC_HEADERS
