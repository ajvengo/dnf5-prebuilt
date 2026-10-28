/*
 * Linux-only APIs used by dnf5, implemented with their macOS equivalents.
 * Force-included (-include) into every dnf5 translation unit on macOS.
 */
#ifndef DNF5_PREBUILT_COMPAT_MACOS_H
#define DNF5_PREBUILT_COMPAT_MACOS_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* pipe2(): pipe() + fcntl(). Not atomic with respect to fork(), which is
 * acceptable for dnf5's use (pipes to subprocesses it spawns itself). */
static inline int pipe2(int pipefd[2], int flags) {
    if (pipe(pipefd) == -1) {
        return -1;
    }
    for (int i = 0; i < 2; ++i) {
        if ((flags & O_CLOEXEC) && fcntl(pipefd[i], F_SETFD, FD_CLOEXEC) == -1) {
            goto fail;
        }
        if ((flags & O_NONBLOCK) &&
            fcntl(pipefd[i], F_SETFL, fcntl(pipefd[i], F_GETFL) | O_NONBLOCK) == -1) {
            goto fail;
        }
    }
    return 0;
fail : {
    int saved_errno = errno;
    close(pipefd[0]);
    close(pipefd[1]);
    errno = saved_errno;
    return -1;
}
}

/* renameat2(): only RENAME_EXCHANGE is used; macOS calls it RENAME_SWAP. */
#ifndef RENAME_EXCHANGE
#define RENAME_EXCHANGE (1 << 1)
#endif
static inline int renameat2(int olddirfd, const char * oldpath, int newdirfd, const char * newpath, unsigned int flags) {
    unsigned int mac_flags = 0;
    if (flags & RENAME_EXCHANGE) {
        mac_flags |= RENAME_SWAP;
    }
    return renameatx_np(olddirfd, oldpath, newdirfd, newpath, mac_flags);
}

/* Mount namespaces do not exist on macOS (only used for bootc systems). */
#ifndef CLONE_NEWNS
#define CLONE_NEWNS 0x00020000
#endif
static inline int unshare(int flags) {
    (void)flags;
    errno = ENOSYS;
    return -1;
}

#ifdef __cplusplus
}
#endif

#endif /* DNF5_PREBUILT_COMPAT_MACOS_H */
