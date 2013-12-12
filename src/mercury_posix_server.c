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
 * opendir
 */
static hg_ptr_t
hg_posix_opendir(const char *dirname)
{
    return (hg_ptr_t) opendir(dirname);
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
 * rewinddir
 */
static hg_uint8_t
hg_posix_rewinddir(hg_ptr_t dirp)
{
    rewinddir((DIR*) dirp);

    return 1;
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
    MERCURY_HANDLER_GEN_LOG_MESSAGE("getcwd");
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
MERCURY_HANDLER_GEN_CALLBACK_STUB(open_cb, open,
        MERCURY_GEN_TRUE, hg_int32_t,
        MERCURY_GEN_TRUE, open_in_t, open_in_params,
        MERCURY_GEN_FALSE, open_out_t, ,
        MERCURY_GEN_FALSE, )
#else
MERCURY_HANDLER_GEN_CALLBACK_STUB(open64_cb, open64,
        MERCURY_GEN_TRUE, hg_int32_t,
        MERCURY_GEN_TRUE, open_in_t, open_in_params,
        MERCURY_GEN_FALSE, open_out_t, ,
        MERCURY_GEN_FALSE, )
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
    MERCURY_HANDLER_GEN_LOG_MESSAGE("readdir");
    direntp = readdir(dirp);

    /* Fill output structure */
    out_struct.dirent_out.d_ino = direntp->d_ino;
    out_struct.dirent_out.d_off = direntp->d_off;
    out_struct.dirent_out.d_reclen = direntp->d_reclen;
    out_struct.dirent_out.d_type = direntp->d_type;
    out_struct.dirent_out.d_name = direntp->d_name;

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
    (hg_posix_close) \
    (dup) \
    (dup2) \
    (fchdir) \
    (fchmod) \
    (fchown) \
    (fdatasync) \
    (fpathconf) \
    (fsync) \
    (hg_posix_closedir) \
    (lchown) \
    (link) \
    (lockf) \
    (mkdir) \
    (mkfifo) \
    (mknod) \
    (hg_posix_opendir) \
    (pathconf) \
    (hg_posix_pipe) \
    (hg_posix_read) \
    (rename) \
    (hg_posix_rewinddir) \
    (rmdir) \
    (symlink) \
    (umask) \
    (unlink) \
    (hg_posix_utime) \
    (hg_posix_write)

#ifndef HG_POSIX_HAS_OPEN64
#define LARGE_FILE_REGISTER_SEQ \
    (creat) \
    (ftruncate) \
    (lseek) \
    (hg_posix_pread) \
    (hg_posix_pwrite) \
    (truncate) \
    (__fxstat) \
    (__xstat) \
    (__lxstat)
#else
#define LARGE_FILE_REGISTER_SEQ \
    (creat64) \
    (ftruncate64) \
    (lseek64) \
    (hg_posix_pread64) \
    (hg_posix_pwrite64) \
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

    MERCURY_HANDLER_REGISTER("getcwd", getcwd_cb, getcwd_in_t, getcwd_out_t);
#ifndef HG_POSIX_HAS_OPEN64
    MERCURY_HANDLER_REGISTER("open", open_cb, open_in_t, open_out_t);
#else
    MERCURY_HANDLER_REGISTER("open64", open64_cb, open_in_t, open_out_t);
#endif
    MERCURY_HANDLER_REGISTER("readdir", readdir_cb, readdir_in_t, readdir_out_t);
    MERCURY_HANDLER_REGISTER("sync", sync_cb, void, void);
}

/******************************************************************************/
int
main(int argc, char *argv[])
{
    na_class_t *network_class = NULL;
    int hg_ret, na_ret;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <bmi|mpi>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Used by Test Driver */
    printf("Waiting for client...\n");
    fflush(stdout);

    /* Initialize the interface */
    network_class = NA_Initialize(getenv(HG_PORT_NAME), 1);

    hg_ret = HG_Handler_init(network_class);
    if (hg_ret != HG_SUCCESS) {
        fprintf(stderr, "Could not initialize function shipper handler\n");
        return EXIT_FAILURE;
    }

    hg_ret = HG_Bulk_init(network_class);
    if (hg_ret != HG_SUCCESS) {
        fprintf(stderr, "Could not initialize bulk data shipper\n");
        return EXIT_FAILURE;
    }

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

    /* Finalize the interface */
    hg_ret = HG_Bulk_finalize();
    if (hg_ret != HG_SUCCESS) {
        fprintf(stderr, "Could not finalize bulk data shipper\n");
        return EXIT_FAILURE;
    }

    hg_ret = HG_Handler_finalize();
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
