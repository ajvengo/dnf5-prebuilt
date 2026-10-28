/*
 * <sys/auxv.h> replacement for macOS: there is no ELF auxiliary vector.
 * dnf5 only queries AT_HWCAP for 32-bit ARM Linux CPUs.
 */
#ifndef DNF5_PREBUILT_COMPAT_SYS_AUXV_H
#define DNF5_PREBUILT_COMPAT_SYS_AUXV_H

#define AT_HWCAP 16

#ifdef __cplusplus
extern "C" {
#endif

static inline unsigned long getauxval(unsigned long type) {
    (void)type;
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* DNF5_PREBUILT_COMPAT_SYS_AUXV_H */
