/*
 * Copyright (C) 2013-2014 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#include "mercury_posix.h"
#include "mercury_posix_gen.h"
#include "mercury_util/mercury_list.h"

#include <stdarg.h>
#define __USE_GNU
#include <dlfcn.h>

#define REAL_DECL(name,ret,args) \
ret (*__real_ ## name)args = NULL;

#define GET_REAL_DECL(func) \
        if (!(__real_ ## func)) \
        { \
            __real_ ## func = dlsym(RTLD_NEXT, #func); \
        }

static hg_list_entry_t *hg_posix_fd_list_g = NULL;
static HG_INLINE int
hg_posix_fd_equal(hg_list_value_t value1, hg_list_value_t value2)
{
    return *((int*)value1) == *((int*)value2);
}

static HG_INLINE void
hg_posix_store_fd(int fd)
{
    int *fd_buf = (int *) malloc(sizeof(int));
    *fd_buf = fd;
    if (!hg_list_find_data(hg_posix_fd_list_g, hg_posix_fd_equal,
            (hg_list_value_t)fd_buf)) {
        if (!hg_list_append(&hg_posix_fd_list_g, (hg_list_value_t)fd_buf)) {
            HG_LOG_ERROR("Could not append handle to list");
        }
    }
}

static HG_INLINE hg_bool_t
hg_posix_check_fd(int fd)
{
    hg_bool_t ret = 1;

    ret = (hg_list_find_data(hg_posix_fd_list_g, hg_posix_fd_equal,
            (hg_list_value_t)&fd) != NULL);

    return ret;
}

static HG_INLINE void
hg_posix_remove_fd(int fd)
{
    hg_list_entry_t *fd_buf_entry = hg_list_find_data(hg_posix_fd_list_g,
            hg_posix_fd_equal, (hg_list_value_t)&fd);
    int *fd_buf = hg_list_data(fd_buf_entry);
    hg_list_remove_data(&hg_posix_fd_list_g, hg_posix_fd_equal,
            (hg_list_value_t)&fd);
    free(fd_buf);
}

/**
 * access
 */
int
access(const char *pathname, int mode)
{
    return hg_posix_access(pathname, mode);
}

/**
 * chmod
 */
int
chmod(const char *path, mode_t mode)
{
    return hg_posix_chmod(path, mode);
}

/**
 * chown
 */
int
chown(const char *path, uid_t owner, gid_t group)
{
    return hg_posix_chown(path, owner, group);
}

/**
 * creat
 */
#ifndef HG_POSIX_HAS_CREAT64
int
creat(const char *pathname, mode_t mode)
{
    int ret;

    ret = hg_posix_creat(pathname, mode);

    /* Keep track of fd */
    if (ret != -1) hg_posix_store_fd(ret);

    return ret;
}
#else
int
creat64(const char *pathname, mode_t mode)
{
    int ret;

    ret = hg_posix_creat64(pathname, mode);

    /* Keep track of fd */
    if (ret != -1) hg_posix_store_fd(ret);

    return ret;

}
#endif

/**
 * close
 */
REAL_DECL(close, int, (int));
int
close(int fd)
{
    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(close);
        return __real_close(fd);
    }
    hg_posix_remove_fd(fd);
    return hg_posix_close(fd);
}

/**
 * closedir
 */
int
closedir(DIR *dirp)
{
    return hg_posix_closedir((hg_ptr_t)dirp);
}

/**
 * dup
 */
REAL_DECL(dup, int, (int));
int
dup(int oldfd)
{
    int ret;

    if (!hg_posix_check_fd(oldfd)) {
        GET_REAL_DECL(dup);
        ret = __real_dup(oldfd);
        return ret;
    }
    ret = hg_posix_dup(oldfd);

    /* Keep track of fd */
    if (ret != -1) hg_posix_store_fd(ret);

    return ret;
}

/**
 * dup2
 */
REAL_DECL(dup2, int, (int, int));
int
dup2(int oldfd, int newfd)
{
    int ret;

    if (!hg_posix_check_fd(oldfd)) {
        GET_REAL_DECL(dup2);
        ret = __real_dup2(oldfd, newfd);
        return ret;
    }
    ret = hg_posix_dup2(oldfd, newfd);

    /* Keep track of fd */
    if (ret != -1) hg_posix_store_fd(ret);

    return ret;
}

/**
 * fchdir
 */
REAL_DECL(fchdir, int, (int));
int
fchdir(int fd)
{
    int ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(fchdir);
        ret = __real_fchdir(fd);
        return ret;
    }
    ret = hg_posix_fchdir(fd);
    return ret;
}

/**
 * fchmod
 */
REAL_DECL(fchmod, int, (int, mode_t));
int
fchmod(int fd, mode_t mode)
{
    int ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(fchmod);
        ret = __real_fchmod(fd, mode);
        return ret;
    }
    ret = hg_posix_fchmod(fd, mode);
    return ret;
}

/**
 * fchown
 */
REAL_DECL(fchown, int, (int, uid_t, gid_t));
int
fchown(int fd, uid_t owner, gid_t group)
{
    int ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(fchown);
        ret = __real_fchown(fd, owner, group);
        return ret;
    }
    ret = hg_posix_fchown(fd, owner, group);
    return ret;
}

/**
 * fdatasync
 */
REAL_DECL(fdatasync, int, (int));
int
fdatasync(int fd)
{
    int ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(fdatasync);
        ret = __real_fdatasync(fd);
        return ret;
    }
    ret = hg_posix_fdatasync(fd);
    return ret;
}

/**
 * fpathconf
 */
REAL_DECL(fpathconf, long, (int, int));
long
fpathconf(int fildes, int name)
{
    long ret;

    if (!hg_posix_check_fd(fildes)) {
        GET_REAL_DECL(fpathconf);
        ret = __real_fpathconf(fildes, name);
        return ret;
    }
    ret = hg_posix_fpathconf(fildes, name);
    return ret;
}

/**
 * fsync
 */
REAL_DECL(fsync, int, (int));
int
fsync(int fd)
{
    int ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(fsync);
        ret = __real_fsync(fd);
        return ret;
    }
    ret = hg_posix_fsync(fd);
    return ret;
}

#ifndef HG_POSIX_HAS_FTRUNCATE64
REAL_DECL(ftruncate, int, (int, off_t));
int
ftruncate(int fd, off_t length)
{
    int ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(ftruncate);
        ret = __real_ftruncate(fd, length);
        return ret;
    }
    ret = hg_posix_ftruncate(fd, length);
    return ret;
}
#else
REAL_DECL(ftruncate64, int, (int, off_t));
int
ftruncate64(int fd, off_t length)
{
    int ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(ftruncate64);
        ret = __real_ftruncate64(fd, length);
        return ret;
    }
    ret = hg_posix_ftruncate64(fd, length);
    return ret;
}
#endif

/**
 * getcwd
 */
char *
getcwd(char *buf, size_t size)
{
    getcwd_in_t in_struct;
    getcwd_out_t out_struct;
    char *ret;
    hg_id_t id;
    hg_handle_t handle;
    hg_bool_t func_registered;
    hg_return_t hg_ret;

    /* Init stack if not initialized */
    HG_Hl_init(NULL, 0);

        /* Check whether call has already been registered or not */
    HG_Registered_rpc(HG_CLASS_DEFAULT, "getcwd", &func_registered, &id);
    if (!func_registered) {
        id = MERCURY_REGISTER(HG_CLASS_DEFAULT, "hg_posix_getcwd",
                getcwd_in_t, getcwd_out_t, NULL);
    }

    /* Create HG handle */
    hg_ret = HG_Create(HG_CLASS_DEFAULT, HG_CONTEXT_DEFAULT, NA_ADDR_DEFAULT,
            id, &handle);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not create HG handle");
        ret = NULL;
        goto done;
    }

    /* Fill input structure */
    in_struct.size = size;

    /* Forward call to default target */
    hg_ret = HG_Hl_forward_wait(handle, &in_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not forward call");
        ret = NULL;
        goto done;
    }

    /* Get output */
    hg_ret = HG_Get_output(handle, &out_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not get output");
        ret = NULL;
        goto done;
    }

    /* Get output parameters */
    strcpy(buf, out_struct.string_out);
    ret = buf;

    /* Free output */
    hg_ret = HG_Free_output(handle, &out_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not free output");
        ret = NULL;
        goto done;
    }

    /* Destroy handle */
    hg_ret = HG_Destroy(handle);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not destroy HG handle");
        ret = NULL;
        goto done;
    }

done:
    return ret;
}

/**
 * lchown
 */
int
lchown(const char *path, uid_t owner, gid_t group)
{
    return hg_posix_lchown(path, owner, group);
}

/**
 * link
 */
int
link(const char *oldpath, const char *newpath)
{
    return hg_posix_link(oldpath, newpath);
}

/**
 * lockf
 */
REAL_DECL(lockf, int, (int, int, off_t));
int
lockf(int fildes, int function, off_t size)
{
    int ret;

    if (!hg_posix_check_fd(fildes)) {
        GET_REAL_DECL(lockf);
        ret = __real_lockf(fildes, function, size);
        return ret;
    }
    ret = hg_posix_lockf(fildes, function, size);
    return ret;
}

/**
 * lseek
 */
#ifndef HG_POSIX_HAS_LSEEK64
REAL_DECL(lseek, off_t, (int, off_t, int));
off_t
lseek(int fildes, off_t offset, int whence)
{
    off_t ret;

    if (!hg_posix_check_fd(fildes)) {
        GET_REAL_DECL(lseek);
        ret = __real_lseek(fildes, offset, whence);
        return ret;
    }
    ret = hg_posix_lseek(fildes, offset, whence);
    return ret;
}
#else
REAL_DECL(lseek64, off_t, (int, off_t, int));
off_t
lseek64(int fildes, off_t offset, int whence)
{
    off_t ret;

    if (!hg_posix_check_fd(fildes)) {
        GET_REAL_DECL(lseek64);
        ret = __real_lseek64(fildes, offset, whence);
        return ret;
    }
    ret = hg_posix_lseek64(fildes, offset, whence);
    return ret;
}
#endif

/**
 * mkdir
 */
int
mkdir(const char *path, mode_t mode)
{
    return hg_posix_mkdir(path, mode);
}

/**
 * mkfifo
 */
int
mkfifo(const char *path, mode_t mode)
{
    return hg_posix_mkfifo(path, mode);
}

/**
 * mknod
 */
int
mknod(const char *pathname, mode_t mode, dev_t dev)
{
    return hg_posix_mknod(pathname, mode, dev);
}

/**
 * open
 */
#ifndef HG_POSIX_HAS_OPEN64
MERCURY_GEN_RPC_STUB(hg_posix_open, hg_posix_open,
        MERCURY_GEN_TRUE, hg_int32_t, -1,
        MERCURY_GEN_TRUE, open_in_t, open_in_params,
        MERCURY_GEN_FALSE, open_out_t, ,
        MERCURY_GEN_FALSE, )

int
open(const char *pathname, int flags, ...)
{
    va_list ap;
    int ret;

    va_start(ap, flags);
    if (flags & O_CREAT) {
        ret = hg_posix_open(pathname, flags, va_arg(ap, mode_t));
    } else {
        ret = hg_posix_open(pathname, flags, 0);
    }
    va_end(ap);

    /* Keep track of fd */
    hg_posix_store_fd(ret);

    return ret;
}
#else
MERCURY_GEN_RPC_STUB(hg_posix_open64, hg_posix_open64,
        MERCURY_GEN_TRUE, hg_int32_t, -1,
        MERCURY_GEN_TRUE, open_in_t, open_in_params,
        MERCURY_GEN_FALSE, open_out_t, ,
        MERCURY_GEN_FALSE, )

int
open64(const char *pathname, int flags, ...)
{
    va_list ap;
    int ret;

    va_start(ap, flags);
    if (flags & O_CREAT) {
        ret = hg_posix_open64(pathname, flags, va_arg(ap, mode_t));
    } else {
        ret = hg_posix_open64(pathname, flags, 0);
    }
    va_end(ap);

    /* Keep track of fd */
    hg_posix_store_fd(ret);

    return ret;
}
#endif

/**
 * opendir
 */
DIR *
opendir(const char *dirname)
{
    return (DIR*)hg_posix_opendir(dirname);
}

/**
 * pathconf
 */
long
pathconf(const char *path, int name)
{
    return hg_posix_pathconf(path, name);
}

/**
 * pipe
 */
REAL_DECL(pipe, int, (int fildes[2]));
int
pipe(int fildes[2])
{
    int ret;

    if (!hg_posix_check_fd(fildes[0]) || !hg_posix_check_fd(fildes[1])) {
        GET_REAL_DECL(pipe);
        ret = __real_pipe(fildes);
        return ret;
    }

    /* TODO A very clean implementation would require an additional mercury proc
     * that encodes and decodes an array of count types. Here we have only
     * two integers so it is simpler like this for now. */
    ret = hg_posix_pipe(fildes[0], fildes[1]);

    /* Keep track of fd */
    hg_posix_store_fd(ret);

    return ret;
}

/**
 * pread
 * TODO for now for convenience just map to our own posix_pread prototype
 */
#ifndef HG_POSIX_HAS_PREAD64
REAL_DECL(pread, ssize_t, (int, void *, size_t, off_t));
ssize_t
pread(int fd, void *buf, size_t count, off_t offset)
{
    ssize_t ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(pread);
        ret = __real_pread(fd, buf, count, offset);
        return ret;
    }
    ret = hg_posix_pread(fd, offset, buf, count);
    return ret;
}
#else
REAL_DECL(pread64, ssize_t, (int, void *, size_t, off_t));
ssize_t
pread64(int fd, void *buf, size_t count, off_t offset)
{
    ssize_t ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(pread64);
        ret = __real_pread64(fd, buf, count, offset);
        return ret;
    }
    ret = hg_posix_pread64(fd, offset, buf, count);
    return ret;
}
#endif

/**
 * pwrite
 * TODO for now for convenience just map to our own posix_pwrite prototype
 */
#ifndef HG_POSIX_HAS_PWRITE64
REAL_DECL(pwrite, ssize_t, (int, const void *, size_t, off_t));
ssize_t
pwrite(int fd, const void *buf, size_t count, off_t offset)
{
    ssize_t ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(pwrite);
        ret = __real_pwrite(fd, buf, count, offset);
        return ret;
    }
    ret = hg_posix_pwrite(fd, offset, (void*)buf, count);
    return ret;
}
#else
REAL_DECL(pwrite64, ssize_t, (int, const void *, size_t, off_t));
ssize_t
pwrite64(int fd, const void *buf, size_t count, off_t offset)
{
    ssize_t ret;

    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(pwrite64);
        ret = __real_pwrite64(fd, buf, count, offset);
        return ret;
    }
    ret = hg_posix_pwrite64(fd, offset, (void*)buf, count);
    return ret;
}
#endif

/**
 * read
 */
REAL_DECL(read, ssize_t, (int, void*, size_t));
ssize_t
read(int fd, void *buf, size_t count)
{
    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(read);
        return __real_read(fd, buf, count);
    }
    return hg_posix_read(fd, buf, count);
}


/**
 * readdir
 */
static struct dirent *
hg_posix_readdir(DIR *dirp)
{
    readdir_in_t in_struct;
    readdir_out_t out_struct;
    static struct dirent dirent_ret;
    struct dirent *ret;
    hg_id_t id;
    hg_handle_t handle;
    hg_bool_t func_registered;
    hg_return_t hg_ret;

    /* Init stack if not initialized */
    HG_Hl_init(NULL, 0);

    /* Check whether call has already been registered or not */
    HG_Registered_rpc(HG_CLASS_DEFAULT, "readdir", &func_registered, &id);
    if (!func_registered) {
        id = MERCURY_REGISTER(HG_CLASS_DEFAULT, "hg_posix_readdir",
                readdir_in_t, readdir_out_t, NULL);
    }

    /* Create HG handle */
    hg_ret = HG_Create(HG_CLASS_DEFAULT, HG_CONTEXT_DEFAULT, NA_ADDR_DEFAULT,
            id, &handle);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not create HG handle");
        ret = NULL;
        goto done;
    }

    /* Fill input structure */
    in_struct.dirp = (hg_ptr_t)dirp;

    /* Forward call to default target */
    hg_ret = HG_Hl_forward_wait(handle, &in_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not forward call");
        ret = NULL;
        goto done;
    }

    /* Get output */
    hg_ret = HG_Get_output(handle, &out_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not get output");
        ret = NULL;
        goto done;
    }

    /* Get output parameters */
    dirent_ret.d_ino = out_struct.dirent_out.d_ino;
    dirent_ret.d_off = out_struct.dirent_out.d_off;
    dirent_ret.d_reclen = out_struct.dirent_out.d_reclen;
    dirent_ret.d_type = out_struct.dirent_out.d_type;
    strcpy(dirent_ret.d_name, out_struct.dirent_out.d_name);

    /* Free output */
    hg_ret = HG_Free_output(handle, &out_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not free output");
        ret = NULL;
        goto done;
    }

    /* Destroy handle */
    hg_ret = HG_Destroy(handle);
    if (hg_ret != HG_SUCCESS) {
        HG_LOG_ERROR("Could not destroy HG handle");
        ret = NULL;
        goto done;
    }

    ret = (dirent_ret.d_ino) ? &dirent_ret : NULL;

done:
    return ret;
}

#ifndef HG_POSIX_HAS_READDIR64
struct dirent *
readdir(DIR *dirp)
{
    return hg_posix_readdir(dirp);
}
#else
struct dirent64 *
readdir64(DIR *dirp)
{
    return (struct dirent64 *) hg_posix_readdir(dirp);
}
#endif

/**
 * rename
 */
int
rename(const char *old, const char *new)
{
    return hg_posix_rename(old, new);
}

/**
 * rewinddir
 */
void
rewinddir(DIR *dirp)
{
    (void) hg_posix_rewinddir((hg_ptr_t)dirp);
}

/**
 * rmdir
 */
int
rmdir(const char *pathname)
{
    return hg_posix_rmdir(pathname);
}

/**
 * sync (not necessary)
 */
void
sync(void)
{
    hg_posix_sync();
}

/**
 * symlink
 */
int
symlink(const char *oldpath, const char *newpath)
{
    return hg_posix_symlink(oldpath, newpath);
}

/**
 * truncate
 */
#ifndef HG_POSIX_HAS_TRUNCATE64
int
truncate(const char *path, off_t length)
{
    return hg_posix_truncate(path, length);
}
#else
int
truncate64(const char *path, off_t length)
{
    return hg_posix_truncate64(path, length);
}
#endif

/**
 * umask
 */
mode_t
umask(mode_t cmask)
{
    return hg_posix_umask(cmask);
}

/**
 * unlink
 */
int
unlink(const char *pathname)
{
    return hg_posix_unlink(pathname);
}

/**
 * utime
 */
int
utime(const char *path, const struct utimbuf *times)
{
    hg_utimbuf_t hg_utimbuf_times;

    hg_utimbuf_times.actime = times->actime;
    hg_utimbuf_times.modtime = times->modtime;

    return hg_posix_utime(path, hg_utimbuf_times);
}

/**
 * write
 */
REAL_DECL(write, int, (int, const void *, size_t));
ssize_t
write(int fd, const void *buf, size_t count)
{
    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(write);
        return __real_write(fd, buf, count);
    }
    return hg_posix_write(fd, (void*)buf, count);
}

/* stat wrappers */
#ifndef HG_POSIX_HAS_FSTAT64
int
__fxstat(int __ver, int __fildes, struct stat *__stat_buf)
{
    return hg_posix___fxstat(__ver, __fildes, __stat_buf);
}
#else
int
__fxstat64(int __ver, int __fildes, struct stat64 *__stat_buf)
{
    return hg_posix___fxstat64(__ver, __fildes, __stat_buf);
}
#endif

#ifndef HG_POSIX_HAS_STAT64
int
__xstat(int __ver, const char *__filename, struct stat *__stat_buf)
{
    return hg_posix___xstat(__ver, __filename, __stat_buf);
}
#else
int
__xstat64(int __ver, const char *__filename, struct stat64 *__stat_buf)
{
    return hg_posix___xstat64(__ver, __filename, __stat_buf);
}
#endif

#ifndef HG_POSIX_HAS_LSTAT64
int
__lxstat(int __ver, const char *__filename, struct stat *__stat_buf)
{
    return hg_posix___lxstat(__ver, __filename, __stat_buf);
}
#else
int
__lxstat64(int __ver, const char *__filename, struct stat64 *__stat_buf)
{
    return hg_posix___lxstat64(__ver, __filename, __stat_buf);
}
#endif
