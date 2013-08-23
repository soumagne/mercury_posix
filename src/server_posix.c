/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#include "mercury_posix_macros.h"
#include "mercury_posix_proc.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* chmod */
MERCURY_POSIX_GEN_CALLBACK_STUB(chmod,
        hg_int32_t,
        (hg_string_t)(hg_mode_t),
)

/* chown */
MERCURY_POSIX_GEN_CALLBACK_STUB(chown,
        hg_int32_t,
        (hg_string_t)(hg_uid_t)(hg_gid_t),
)

/* creat */
MERCURY_POSIX_GEN_CALLBACK_STUB(creat,
        hg_int32_t,
        (hg_string_t)(hg_mode_t),
)
MERCURY_POSIX_GEN_CALLBACK_STUB(creat64,
        hg_int32_t,
        (hg_string_t)(hg_mode_t),
)

/* close */
MERCURY_POSIX_GEN_CALLBACK_STUB(close,
        hg_int32_t,
        (hg_int32_t),
)

/* dup */
MERCURY_POSIX_GEN_CALLBACK_STUB(dup,
        hg_int32_t,
        (hg_int32_t),
)

/* dup2 */
MERCURY_POSIX_GEN_CALLBACK_STUB(dup2,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t),
)

/* fchdir */
MERCURY_POSIX_GEN_CALLBACK_STUB(fchdir,
        hg_int32_t,
        (hg_int32_t),
)

/* fchmod */
MERCURY_POSIX_GEN_CALLBACK_STUB(fchmod,
        hg_int32_t,
        (hg_int32_t)(hg_mode_t),
)

/* fchown */
MERCURY_POSIX_GEN_CALLBACK_STUB(fchown,
        hg_int32_t,
        (hg_int32_t)(hg_uid_t)(hg_gid_t),
)

/* fdatasync */
MERCURY_POSIX_GEN_CALLBACK_STUB(fdatasync,
        hg_int32_t,
        (hg_int32_t),
)

/* fpathconf */
MERCURY_POSIX_GEN_CALLBACK_STUB(fpathconf,
        hg_int64_t,
        (hg_int32_t)(hg_int32_t),
)

/* fsync */
MERCURY_POSIX_GEN_CALLBACK_STUB(fsync,
        hg_int32_t,
        (hg_int32_t),
)

/* ftruncate */
MERCURY_POSIX_GEN_CALLBACK_STUB(ftruncate,
        hg_int32_t,
        (hg_int32_t)(hg_off_t),
)
MERCURY_POSIX_GEN_CALLBACK_STUB(ftruncate64,
        hg_int32_t,
        (hg_int32_t)(hg_off_t),
)

/* lchown */
MERCURY_POSIX_GEN_CALLBACK_STUB(lchown,
        hg_int32_t,
        (hg_string_t)(hg_uid_t)(hg_gid_t),
)

/* link */
MERCURY_POSIX_GEN_CALLBACK_STUB(link,
        hg_int32_t,
        (hg_string_t)(hg_string_t),
)

/* lockf */
MERCURY_POSIX_GEN_CALLBACK_STUB(lockf,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t)(hg_off_t),
)

/* lseek */
MERCURY_POSIX_GEN_CALLBACK_STUB(lseek,
        hg_off_t,
        (hg_int32_t)(hg_off_t)(hg_int32_t),
)
MERCURY_POSIX_GEN_CALLBACK_STUB(lseek64,
        hg_off_t,
        (hg_int32_t)(hg_off_t)(hg_int32_t),
)

/* mkdir */
MERCURY_POSIX_GEN_CALLBACK_STUB(mkdir,
        hg_int32_t,
        (hg_string_t)(hg_mode_t),
)

/* mkfifo */
MERCURY_POSIX_GEN_CALLBACK_STUB(mkfifo,
        hg_int32_t,
        (hg_string_t)(hg_mode_t),
)

/* mknod */
MERCURY_POSIX_GEN_CALLBACK_STUB(mknod,
        hg_int32_t,
        (hg_string_t)(hg_mode_t)(hg_dev_t),
)

/**
 * open
 */
#define open_in_params ((hg_string_t)(pathname))((hg_int32_t)(flags))((hg_uint32_t)(mode))

HG_GEN_STRUCT(open_in_t, open_in_params)

static HG_INLINE int
hg_proc_open_in_t(hg_proc_t proc, void *data)
{
    open_in_t *struct_data = (open_in_t *) data;
    hg_proc_hg_string_t(proc, &struct_data->pathname);
    hg_proc_hg_int32_t(proc, &struct_data->flags);
    if (struct_data->flags & O_CREAT) {
        hg_proc_hg_uint32_t(proc, &struct_data->mode);
    }
    return 1;
}

MERCURY_GEN_PROC(open_out_t, ((hg_int32_t)(ret)))
MERCURY_HANDLER_GEN_CALLBACK_STUB(open_cb, open,
        MERCURY_GEN_TRUE, hg_int32_t,
        MERCURY_GEN_TRUE, open_in_t, open_in_params,
        MERCURY_GEN_FALSE, open_out_t, ,
        MERCURY_GEN_FALSE, )

/* pathconf */
MERCURY_POSIX_GEN_CALLBACK_STUB(pathconf,
        hg_int64_t,
        (hg_string_t)(hg_int32_t),
)

/* read */
MERCURY_POSIX_GEN_CALLBACK_BULK_STUB(read,
        hg_ssize_t,
        (int32_t),
        ,
        MERCURY_GEN_FALSE
)

/* rename */
MERCURY_POSIX_GEN_CALLBACK_STUB(rename,
        hg_int32_t,
        (hg_string_t)(hg_string_t),
)

/* rmdir */
MERCURY_POSIX_GEN_CALLBACK_STUB(rmdir,
        hg_int32_t,
        (hg_string_t),
)

/* sync */
MERCURY_POSIX_GEN_CALLBACK_STUB_NOINPUT_NORET(sync)

/* symlink */
MERCURY_POSIX_GEN_CALLBACK_STUB(symlink,
        hg_int32_t,
        (hg_string_t)(hg_string_t),
)

/* truncate */
MERCURY_POSIX_GEN_CALLBACK_STUB(truncate,
        hg_int32_t,
        (hg_string_t)(hg_off_t),
)
MERCURY_POSIX_GEN_CALLBACK_STUB(truncate64,
        hg_int32_t,
        (hg_string_t)(hg_off_t),
)

/* umask */
MERCURY_POSIX_GEN_CALLBACK_STUB(umask,
        hg_mode_t,
        (hg_mode_t),
)

/* unlink */
MERCURY_POSIX_GEN_CALLBACK_STUB(unlink,
        hg_int32_t,
        (hg_string_t),
)

/**
 * write
 */
static hg_ssize_t hg_posix_write(hg_int32_t fd, void *buf, hg_uint64_t count)
{
    return write(fd, buf, count);
}

MERCURY_POSIX_GEN_CALLBACK_BULK_STUB(hg_posix_write,
        hg_ssize_t,
        (hg_int32_t), ,
        MERCURY_GEN_TRUE
)

/* stat wrappers */
MERCURY_POSIX_GEN_CALLBACK_STUB(__fxstat,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t), (hg_stat_t)
)
MERCURY_POSIX_GEN_CALLBACK_STUB(__fxstat64,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t), (hg_stat_t)
)

MERCURY_POSIX_GEN_CALLBACK_STUB(__xstat,
        hg_int32_t,
        (hg_int32_t)(hg_string_t), (hg_stat_t)
)
MERCURY_POSIX_GEN_CALLBACK_STUB(__xstat64,
        hg_int32_t,
        (hg_int32_t)(hg_string_t), (hg_stat_t)
)

MERCURY_POSIX_GEN_CALLBACK_STUB(__lxstat,
        hg_int32_t,
        (hg_int32_t)(hg_string_t), (hg_stat_t)
)
MERCURY_POSIX_GEN_CALLBACK_STUB(__lxstat64,
        hg_int32_t,
        (hg_int32_t)(hg_string_t), (hg_stat_t)
)

/******************************************************************************/

#define REGISTER_SEQ \
    (chmod) \
    (chown) \
    (creat) \
    (creat64) \
    (close) \
    (dup) \
    (dup2) \
    (fchdir) \
    (fchmod) \
    (fchown) \
    (fdatasync) \
    (fpathconf) \
    (fsync) \
    (ftruncate) \
    (ftruncate64) \
    (lchown) \
    (link) \
    (lockf) \
    (lseek) \
    (lseek64) \
    (mkdir) \
    (mkfifo) \
    (mknod) \
    (pathconf) \
    (read) \
    (rename) \
    (rmdir) \
    (symlink) \
    (truncate) \
    (truncate64) \
    (umask) \
    (unlink) \
    (hg_posix_write) \
    (__fxstat) \
    (__fxstat64) \
    (__xstat) \
    (__xstat64) \
    (__lxstat) \
    (__lxstat64)

#define MERCURY_POSIX_HANDLER_REGISTER_SEQ(r, data, elem) \
    MERCURY_POSIX_HANDLER_REGISTER(elem);

static void
register_posix(void)
{
    BOOST_PP_SEQ_FOR_EACH(MERCURY_POSIX_HANDLER_REGISTER_SEQ, , REGISTER_SEQ)

    MERCURY_HANDLER_REGISTER("open", open_cb, open_in_t, open_out_t);
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
