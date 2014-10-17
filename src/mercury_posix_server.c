/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <dirent.h>

#include "mercury_posix_types.h"
#include "mercury_proc_string.h"

/**
 * access
 */
static hg_int32_t
hg_posix_access(hg_const_string_t pathname, hg_int32_t mode)
{
    return access(pathname, mode);
}

/**
 * chmod
 */
static hg_int32_t
hg_posix_chmod(hg_const_string_t path, hg_mode_t mode)
{
    return chmod(path, mode);
}

/**
 * chown
 */
static hg_int32_t
hg_posix_chown(hg_const_string_t path, hg_uid_t owner, hg_gid_t group)
{
    return chown(path, owner, group);
}

/**
 * creat
 */
#ifndef HG_POSIX_HAS_CREAT64
static hg_int32_t
hg_posix_creat(hg_const_string_t pathname, hg_mode_t mode)
{
    return creat(pathname, mode);
}
#else
static hg_int32_t
hg_posix_creat64(hg_const_string_t pathname, hg_mode_t mode)
{
    return creat64(pathname, mode);
}
#endif

/**
 * close
 */
static hg_int32_t
hg_posix_close(hg_int32_t fd)
{
    return close(fd);
}

/**
 * closedir
 */
static hg_int32_t
hg_posix_closedir(hg_ptr_t dirp)
{
    return closedir((DIR*) dirp);
}

/**
 * dup
 */
static hg_int32_t
hg_posix_dup(hg_int32_t oldfd)
{
    return dup(oldfd);
}

/**
 * dup2
 */
static hg_int32_t
hg_posix_dup2(hg_int32_t oldfd, hg_int32_t newfd)
{
    return dup2(oldfd, newfd);
}

/**
 * fchdir
 */
static hg_int32_t
hg_posix_fchdir(hg_int32_t fd)
{
    return fchdir(fd);
}

/**
 * fchmod
 */
static hg_int32_t
hg_posix_fchmod(hg_int32_t fd, hg_mode_t mode)
{
    return fchmod(fd, mode);
}

/**
 * fchown
 */
static hg_int32_t
hg_posix_fchown(hg_int32_t fd, hg_uid_t owner, hg_gid_t group)
{
    return fchown(fd, owner, group);
}

/**
 * fdatasync
 */
static hg_int32_t
hg_posix_fdatasync(hg_int32_t fd)
{
    return fdatasync(fd);
}

/**
 * fpathconf
 */
static hg_long_t
hg_posix_fpathconf(hg_int32_t fildes, hg_int32_t name)
{
    return fpathconf(fildes, name);
}

/**
 * fsync
 */
static hg_int32_t
hg_posix_fsync(hg_int32_t fd)
{
    return fsync(fd);
}

/**
 * ftruncate
 */
#ifndef HG_POSIX_HAS_FTRUNCATE64
static hg_int32_t
hg_posix_ftruncate(hg_int32_t fd, hg_off_t length)
{
    return ftruncate(fd, length);
}
#else
static hg_int32_t
hg_posix_ftruncate64(hg_int32_t fd, hg_off_t length)
{
    return ftruncate64(fd, length);
}
#endif

/**
 * lchown
 */
static hg_int32_t
hg_posix_lchown(hg_const_string_t path, hg_uid_t owner, hg_gid_t group)
{
    return lchown(path, owner, group);
}

/**
 * link
 */
static hg_int32_t
hg_posix_link(hg_const_string_t oldpath, hg_const_string_t newpath)
{
    return link(oldpath, newpath);
}

/**
 * lockf
 */
static hg_int32_t
hg_posix_lockf(hg_int32_t fildes, hg_int32_t function, hg_off_t size)
{
    return lockf(fildes, function, size);
}

/**
 * lseek
 */
#ifndef HG_POSIX_HAS_LSEEK64
static hg_off_t
hg_posix_lseek(hg_int32_t fildes, hg_off_t offset, hg_int32_t whence)
{
    return lseek(fildes, offset, whence);
}
#else
static hg_off_t
hg_posix_lseek64(hg_int32_t fildes, hg_off_t offset, hg_int32_t whence)
{
    return lseek64(fildes, offset, whence);
}
#endif

/**
 * mkdir
 */
static hg_int32_t
hg_posix_mkdir(hg_const_string_t path, hg_mode_t mode)
{
    return mkdir(path, mode);
}

/**
 * mkfifo
 */
static hg_int32_t
hg_posix_mkfifo(hg_const_string_t path, hg_mode_t mode)
{
    return mkfifo(path, mode);
}

/**
 * mknod
 */
static hg_int32_t
hg_posix_mknod(hg_const_string_t pathname, hg_mode_t mode, hg_dev_t dev)
{
    return mknod(pathname, mode, dev);
}

/**
 * open
 */
#ifndef HG_POSIX_HAS_OPEN64
static hg_int32_t
hg_posix_open(hg_const_string_t pathname, hg_int32_t flags, hg_uint32_t mode)
{
    return open(pathname, flags, mode);
}
#else
static hg_int32_t
hg_posix_open64(hg_const_string_t pathname, hg_int32_t flags, hg_uint32_t mode)
{
    return open64(pathname, flags, mode);
}
#endif


/**
 * opendir
 */
static hg_ptr_t
hg_posix_opendir(const char *dirname)
{
    return (hg_ptr_t) opendir(dirname);
}

/**
 * pathconf
 */
static hg_long_t
hg_posix_pathconf(hg_const_string_t path, hg_int32_t name)
{
    return pathconf(path, name);
}

/**
 * pipe
 */
static hg_int32_t
hg_posix_pipe(hg_int32_t fildes0, hg_int32_t fildes1)
{
    hg_int32_t fildes[2];

    fildes[0] = fildes0;
    fildes[1] = fildes1;

    return pipe(fildes);
}

/**
 * pread
 */
#ifndef HG_POSIX_HAS_PREAD64
static hg_ssize_t
hg_posix_pread(hg_int32_t fd, hg_off_t offset, void *buf, hg_uint64_t count)
{
    return pread(fd, buf, count, offset);
}
#else
static hg_ssize_t
hg_posix_pread64(hg_int32_t fd, hg_off_t offset, void *buf, hg_uint64_t count)
{
    return pread64(fd, buf, count, offset);
}
#endif

/**
 * pwrite
 */
#ifndef HG_POSIX_HAS_PWRITE64
static hg_ssize_t
hg_posix_pwrite(hg_int32_t fd, hg_off_t offset, void *buf, hg_uint64_t count)
{
    return pwrite(fd, buf, count, offset);
}
#else
static hg_ssize_t
hg_posix_pwrite64(hg_int32_t fd, hg_off_t offset, void *buf, hg_uint64_t count)
{
    return pwrite64(fd, buf, count, offset);
}
#endif

/**
 * read
 */
static hg_ssize_t
hg_posix_read(hg_int32_t fd, void *buf, hg_uint64_t count)
{
    return read(fd, buf, count);
}

/**
 * readdir
 */


/**
 * rename
 */
static hg_int32_t
hg_posix_rename(hg_const_string_t old, hg_const_string_t new)
{
    return rename(old, new);
}

/**
 * rewinddir
 */
static hg_uint8_t
hg_posix_rewinddir(hg_ptr_t dirp)
{
    rewinddir((DIR*) dirp);

    return 1;
}

/**
 * rmdir
 */
static hg_int32_t
hg_posix_rmdir(hg_const_string_t pathname)
{
    return rmdir(pathname);
}

/**
 * sync
 */
static void
hg_posix_sync(void)
{
    sync();
}

/**
 * symlink
 */
static hg_int32_t
hg_posix_symlink(hg_const_string_t oldpath, hg_const_string_t newpath)
{
    return symlink(oldpath, newpath);
}

/**
 * truncate
 */
#ifndef HG_POSIX_HAS_TRUNCATE64
static hg_int32_t
hg_posix_truncate(hg_const_string_t path, hg_off_t length)
{
    return truncate(path, length);
}
#else
static hg_int32_t
hg_posix_truncate64(hg_const_string_t path, hg_off_t length)
{
    return truncate64(path, length);
}
#endif

/**
 * umask
 */
static hg_mode_t
hg_posix_umask(hg_mode_t cmask)
{
    return umask(cmask);
}

/**
 * unlink
 */
static hg_int32_t
hg_posix_unlink(hg_const_string_t pathname)
{
    return unlink(pathname);
}

/**
 * utime
 */
static hg_int32_t
hg_posix_utime(const char *filename, hg_utimbuf_t times)
{
    return utime(filename, &times);
}

/**
 * write
 */
static hg_ssize_t
hg_posix_write(hg_int32_t fd, void *buf, hg_uint64_t count)
{
    return write(fd, buf, count);
}

/* stat wrappers */
#ifndef HG_POSIX_HAS_FSTAT64
static hg_int32_t
hg_posix___fxstat(hg_int32_t __ver, hg_int32_t __fildes, hg_stat_t *__stat_buf)
{
    return __fxstat(__ver, __fildes, __stat_buf);
}
#else
static hg_int32_t
hg_posix___fxstat64(hg_int32_t __ver, hg_int32_t __fildes, hg_stat_t *__stat_buf)
{
    return __fxstat64(__ver, __fildes, __stat_buf);
}
#endif

#ifndef HG_POSIX_HAS_STAT64
static hg_int32_t
hg_posix___xstat(hg_int32_t __ver, hg_const_string_t __filename, hg_stat_t *__stat_buf)
{
    return __xstat(__ver, __filename, __stat_buf);
}
#else
static hg_int32_t
hg_posix___xstat64(hg_int32_t __ver, hg_const_string_t __filename, hg_stat_t *__stat_buf)
{
    return __xstat64(__ver, __filename, __stat_buf);
}
#endif

#ifndef HG_POSIX_HAS_LSTAT64
static hg_int32_t
hg_posix___lxstat(hg_int32_t __ver, hg_const_string_t __filename, hg_stat_t *__stat_buf)
{
    return __lxstat(__ver, __filename, __stat_buf);
}
#else
static hg_int32_t
hg_posix___lxstat64(hg_int32_t __ver, hg_const_string_t __filename, hg_stat_t *__stat_buf)
{
    return __lxstat64(__ver, __filename, __stat_buf);
}
#endif


#define MERCURY_POSIX_SERVER /* Define to generate server stubs */
#include "mercury_posix_gen.h"

/* Only routines that can't automatically be generated are defined here */

/**
 * getcwd
 */
static int
getcwd_cb(hg_handle_t handle)
{
    int hg_ret = HG_SUCCESS;
    getcwd_in_t in_struct;
    getcwd_out_t out_struct;
    hg_string_t string_out = NULL;
    hg_uint64_t size;

    /* Get input buffer */
    hg_ret = HG_Handler_get_input(handle, &in_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Could not get input struct");
        goto done;
    }

    /* Get parameters */
    size = in_struct.size;

    string_out = malloc(size);

    /* Call function */
    MERCURY_HANDLER_GEN_LOG_MESSAGE("hg_posix_getcwd");
    string_out = getcwd(string_out, size);

    /* Fill output structure */
    out_struct.string_out = string_out;

    /* Free handle and send response back */
    hg_ret = HG_Handler_start_output(handle, &out_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Could not start output");
        goto done;
    }

done:
    free(string_out);

    return hg_ret;
}

/**
 * open
 */
#ifndef HG_POSIX_HAS_OPEN64
MERCURY_HANDLER_GEN_CALLBACK_STUB(open_cb, hg_posix_open,
        MERCURY_GEN_TRUE, hg_int32_t,
        MERCURY_GEN_TRUE, open_in_t, open_in_params,
        MERCURY_GEN_FALSE, open_out_t, ,
        MERCURY_GEN_FALSE, ,
        MERCURY_GEN_TRUE, hg_posix_threadpool_g)
#else
MERCURY_HANDLER_GEN_CALLBACK_STUB(open64_cb, hg_posix_open64,
        MERCURY_GEN_TRUE, hg_int32_t,
        MERCURY_GEN_TRUE, open_in_t, open_in_params,
        MERCURY_GEN_FALSE, open_out_t, ,
        MERCURY_GEN_FALSE, ,
        MERCURY_GEN_TRUE, hg_posix_threadpool_g)
#endif

/**
 * readdir
 */
static int
readdir_cb(hg_handle_t handle)
{
    int hg_ret = HG_SUCCESS;
    readdir_in_t in_struct;
    readdir_out_t out_struct;
    DIR *dirp;
    struct dirent *direntp;

    /* Get input buffer */
    hg_ret = HG_Handler_get_input(handle, &in_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Could not get input struct");
        goto done;
    }

    /* Get parameters */
    dirp = (DIR*) in_struct.dirp;

    /* Call function */
    MERCURY_HANDLER_GEN_LOG_MESSAGE("hg_posix_readdir");
#ifndef HG_POSIX_HAS_READDIR64
    direntp = readdir(dirp);
#else
    direntp = (struct dirent *) readdir64(dirp);
#endif

    /* Fill output structure */
    if (direntp) {
        out_struct.dirent_out.d_ino = direntp->d_ino;
        out_struct.dirent_out.d_off = direntp->d_off;
        out_struct.dirent_out.d_reclen = direntp->d_reclen;
        out_struct.dirent_out.d_type = direntp->d_type;
        out_struct.dirent_out.d_name = direntp->d_name;
    } else {
        out_struct.dirent_out.d_ino = 0;
        out_struct.dirent_out.d_off = 0;
        out_struct.dirent_out.d_reclen = 0;
        out_struct.dirent_out.d_type = 0;
        out_struct.dirent_out.d_name = '\0';
    }

    /* Free handle and send response back */
    hg_ret = HG_Handler_start_output(handle, &out_struct);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Could not start output");
        goto done;
    }

done:
    return hg_ret;
}

/******************************************************************************/
#define REGISTER_SEQ \
    (access) \
    (chmod) \
    (chown) \
    (close) \
    (dup) \
    (dup2) \
    (fchdir) \
    (fchmod) \
    (fchown) \
    (fdatasync) \
    (fpathconf) \
    (fsync) \
    (closedir) \
    (lchown) \
    (link) \
    (lockf) \
    (mkdir) \
    (mkfifo) \
    (mknod) \
    (opendir) \
    (pathconf) \
    (pipe) \
    (read) \
    (rename) \
    (rewinddir) \
    (rmdir) \
    (symlink) \
    (umask) \
    (unlink) \
    (utime) \
    (write)

#ifndef HG_POSIX_HAS_OPEN64
#define LARGE_FILE_REGISTER_SEQ \
    (creat) \
    (ftruncate) \
    (lseek) \
    (pread) \
    (pwrite) \
    (truncate) \
    (__fxstat) \
    (__xstat) \
    (__lxstat)
#else
#define LARGE_FILE_REGISTER_SEQ \
    (creat64) \
    (ftruncate64) \
    (lseek64) \
    (pread64) \
    (pwrite64) \
    (truncate64) \
    (__fxstat64) \
    (__xstat64) \
    (__lxstat64)
#endif

#define MERCURY_POSIX_HANDLER_REGISTER_SEQ(r, data, elem) \
    MERCURY_POSIX_HANDLER_REGISTER(elem);

static void
register_posix(void)
{
    BOOST_PP_SEQ_FOR_EACH(MERCURY_POSIX_HANDLER_REGISTER_SEQ, ,
            REGISTER_SEQ LARGE_FILE_REGISTER_SEQ);

    MERCURY_REGISTER("hg_posix_getcwd", getcwd_in_t, getcwd_out_t, getcwd_cb);
#ifndef HG_POSIX_HAS_OPEN64
    MERCURY_REGISTER("hg_posix_open", open_in_t, open_out_t, open_cb);
#else
    MERCURY_REGISTER("hg_posix_open64", open_in_t, open_out_t, open64_cb);
#endif
    MERCURY_REGISTER("hg_posix_readdir", readdir_in_t, readdir_out_t, readdir_cb);
    MERCURY_REGISTER("hg_posix_sync", void, void, sync_cb);
}

/******************************************************************************/
int
main(int argc, char *argv[])
{
    na_class_t *network_class = NULL;
    int hg_ret, na_ret;

    /* Used by Test Driver */
#ifdef HG_POSIX_HAS_OPEN64
    printf("Running with large file support\n");
#else
    printf("Running without large file support\n");
#endif
    printf("Waiting for client...\n");
    fflush(stdout);
    setvbuf(stdout, NULL, _IONBF, 0);

    /* Initialize the interface */
    network_class = NA_Initialize(getenv(HG_PORT_NAME), 1);

    hg_ret = HG_Init(network_class);
    if (hg_ret != HG_SUCCESS) {
        fprintf(stderr, "Could not initialize function shipper handler\n");
        return EXIT_FAILURE;
    }

    hg_thread_pool_init(8, &hg_posix_threadpool_g);

    /* Register routine */
    register_posix();

    while (1) {
        hg_status_t status;
        /* Receive new function calls */
        hg_ret = HG_Handler_process(10, &status);
        if (hg_ret == HG_SUCCESS && status) {
        }
    }

    printf("Finalizing...\n");

    hg_thread_pool_destroy(hg_posix_threadpool_g);

    /* Finalize the interface */
    hg_ret = HG_Finalize();
    if (hg_ret != HG_SUCCESS) {
        fprintf(stderr, "Could not finalize function shipper handler\n");
        return EXIT_FAILURE;
    }

    na_ret = NA_Finalize(network_class);
    if (na_ret != NA_SUCCESS) {
        fprintf(stderr, "Could not finalize NA interface\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
