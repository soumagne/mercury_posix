/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#ifndef MERCURY_POSIX_H
#define MERCURY_POSIX_H

#include "mercury_posix_config.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>
#include <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

HG_POSIX_EXPORT int access(const char *pathname, int mode);
//HG_POSIX_EXPORT int chdir(const char *path);
HG_POSIX_EXPORT int chmod(const char *path, mode_t mode);
HG_POSIX_EXPORT int chown(const char *path, uid_t owner, gid_t group);
#ifndef HG_POSIX_HAS_CREAT64
HG_POSIX_EXPORT int creat(const char *pathname, mode_t mode);
#else
HG_POSIX_EXPORT int creat64(const char *pathname, mode_t mode);
#endif
HG_POSIX_EXPORT int close(int fd);
HG_POSIX_EXPORT int closedir(DIR *dirp);
HG_POSIX_EXPORT int dup(int oldfd);
HG_POSIX_EXPORT int dup2(int oldfd, int newfd);
HG_POSIX_EXPORT int fchdir(int fd);
HG_POSIX_EXPORT int fchmod(int fd, mode_t mode);
HG_POSIX_EXPORT int fchown(int fd, uid_t owner, gid_t group);
//HG_POSIX_EXPORT int fcntl(int fd, int cmd, ... /* arg */ );
HG_POSIX_EXPORT int fdatasync(int fd);
HG_POSIX_EXPORT long fpathconf(int fildes, int name);
HG_POSIX_EXPORT int fsync(int fd);
#ifndef HG_POSIX_HAS_FTRUNCATE64
HG_POSIX_EXPORT int ftruncate(int fd, off_t length);
#else
HG_POSIX_EXPORT int ftruncate64(int fd, off_t length);
#endif
HG_POSIX_EXPORT char *getcwd(char *buf, size_t size);
HG_POSIX_EXPORT int lchown(const char *path, uid_t owner, gid_t group);
HG_POSIX_EXPORT int link(const char *oldpath, const char *newpath);
HG_POSIX_EXPORT int lockf(int fildes, int function, off_t size);
#ifndef HG_POSIX_HAS_LSEEK64
HG_POSIX_EXPORT off_t lseek(int fildes, off_t offset, int whence);
#else
HG_POSIX_EXPORT off_t lseek64(int fildes, off_t offset, int whence);
#endif
HG_POSIX_EXPORT int mkdir(const char *path, mode_t mode);
HG_POSIX_EXPORT int mkfifo(const char *path, mode_t mode);
HG_POSIX_EXPORT int mknod(const char *pathname, mode_t mode, dev_t dev);
#ifndef HG_POSIX_HAS_OPEN64
HG_POSIX_EXPORT int open(const char *pathname, int flags, ...);
#else
HG_POSIX_EXPORT int open64(const char *pathname, int flags, ...);
#endif
HG_POSIX_EXPORT DIR *opendir(const char *dirname);
HG_POSIX_EXPORT long pathconf(const char *path, int name);
HG_POSIX_EXPORT int pipe(int fildes[2]);
#ifndef HG_POSIX_HAS_PREAD64
HG_POSIX_EXPORT ssize_t pread(int fd, void *buf, size_t count, off_t offset);
#else
HG_POSIX_EXPORT ssize_t pread64(int fd, void *buf, size_t count, off_t offset);
#endif
#ifndef HG_POSIX_HAS_PWRITE64
HG_POSIX_EXPORT ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
#else
HG_POSIX_EXPORT ssize_t pwrite64(int fd, const void *buf, size_t count, off_t offset);
#endif
HG_POSIX_EXPORT ssize_t read(int fd, void *buf, size_t count);
#ifndef HG_POSIX_HAS_READDIR64
HG_POSIX_EXPORT struct dirent *readdir(DIR *dirp);
#else
HG_POSIX_EXPORT struct dirent64 *readdir64(DIR *dirp);
#endif
//HG_POSIX_EXPORT int readdir_r(DIR *restrict dirp, struct dirent *restrict entry,
//       struct dirent **restrict result);
//ssize_t readlink(const char *path, char *buf, size_t bufsiz);
HG_POSIX_EXPORT int rename(const char *old, const char *new);
HG_POSIX_EXPORT void rewinddir(DIR *dirp);
HG_POSIX_EXPORT int rmdir(const char *pathname);
HG_POSIX_EXPORT void sync(void);
HG_POSIX_EXPORT int symlink(const char *oldpath, const char *newpath);
#ifndef HG_POSIX_HAS_TRUNCATE64
HG_POSIX_EXPORT int truncate(const char *path, off_t length);
#else
HG_POSIX_EXPORT int truncate64(const char *path, off_t length);
#endif
HG_POSIX_EXPORT mode_t umask(mode_t cmask);
HG_POSIX_EXPORT int unlink(const char *pathname);
HG_POSIX_EXPORT int utime(const char *path, const struct utimbuf *times);
HG_POSIX_EXPORT ssize_t write(int fd, const void *buf, size_t count);

/* stat wrappers */
#ifndef HG_POSIX_HAS_FSTAT64
HG_POSIX_EXPORT int __fxstat(int __ver, int __fildes, struct stat *__stat_buf);
#else
HG_POSIX_EXPORT int __fxstat64(int __ver, int __fildes, struct stat64 *__stat_buf);
#endif

#ifndef HG_POSIX_HAS_STAT64
HG_POSIX_EXPORT int __xstat(int __ver, const char *__filename,
        struct stat *__stat_buf);
#else
HG_POSIX_EXPORT int __xstat64(int __ver, const char *__filename,
        struct stat64 *__stat_buf);
#endif

#ifndef HG_POSIX_HAS_LSTAT64
HG_POSIX_EXPORT int __lxstat(int __ver, const char *__filename,
        struct stat *__stat_buf);
#else
HG_POSIX_EXPORT int __lxstat64(int __ver, const char *__filename,
        struct stat64 *__stat_buf);
#endif

#ifdef __cplusplus
}
#endif

#endif /* MERCURY_POSIX_H */
