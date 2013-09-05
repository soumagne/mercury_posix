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

#include "mercury_posix_types.h"

/**
 * write
 */
static hg_ssize_t hg_posix_write(hg_int32_t fd, void *buf, hg_uint64_t count)
{
    return write(fd, buf, count);
}

#define MERCURY_POSIX_SERVER
#include "mercury_posix_gen.h"

/**
 * open
 */
#ifndef HG_POSIX_HAS_LARGE_FILE
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

/******************************************************************************/
#define REGISTER_SEQ \
    (access) \
    (chdir) \
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
    (lchown) \
    (link) \
    (lockf) \
    (mkdir) \
    (mkfifo) \
    (mknod) \
    (pathconf) \
    (read) \
    (rename) \
    (rmdir) \
    (symlink) \
    (umask) \
    (unlink) \
    (hg_posix_write)

#ifndef HG_POSIX_HAS_LARGE_FILE
#define LARGE_FILE_REGISTER_SEQ \
    (creat) \
    (ftruncate) \
    (lseek) \
    (truncate) \
    (__fxstat) \
    (__xstat) \
    (__lxstat)
#else
#define LARGE_FILE_REGISTER_SEQ \
    (creat64) \
    (ftruncate64) \
    (lseek64) \
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
            REGISTER_SEQ LARGE_FILE_REGISTER_SEQ)

#ifndef HG_POSIX_HAS_LARGE_FILE
    MERCURY_HANDLER_REGISTER("open", open_cb, open_in_t, open_out_t);
#else
    MERCURY_HANDLER_REGISTER("open64", open64_cb, open_in_t, open_out_t);
#endif
    MERCURY_HANDLER_REGISTER("sync", sync_cb, void, void);
}

/******************************************************************************/
int
main(int argc, char *argv[])
{
    na_class_t *network_class = NULL;
//    unsigned int number_of_peers = 1;
    int hg_ret, na_ret;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <bmi|mpi>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Used by Test Driver */
    printf("Waiting for client...\n");
    fflush(stdout);

    /* Initialize the interface */
    network_class = NA_Initialize(argv[1], getenv(HG_PORT_NAME), 1);

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
        hg_ret = HG_Handler_process(100, &status);
        if (hg_ret == HG_SUCCESS && status) {
//            printf("Call processed\n");
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
