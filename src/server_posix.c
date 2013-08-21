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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* open */
static hg_int32_t
hg_posix_open1(hg_string_t pathname, hg_int32_t flags, hg_uint32_t mode)
{
    return open(pathname, flags, mode);
}

MERCURY_POSIX_HANDLER_GEN_CALLBACK_STUB(hg_posix_open1,
        hg_int32_t,
        (hg_string_t)(hg_int32_t)(hg_uint32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

static hg_int32_t
hg_posix_open2(hg_string_t pathname, hg_int32_t flags)
{
    return open(pathname, flags);
}

MERCURY_POSIX_HANDLER_GEN_CALLBACK_STUB(hg_posix_open2,
        hg_int32_t,
        (hg_string_t)(hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* close */
MERCURY_POSIX_HANDLER_GEN_CALLBACK_STUB(close,
        hg_int32_t,
        (hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* write */
static hg_int64_t hg_posix_write(hg_int32_t fd, void *buf, hg_uint64_t count)
{
    return write(fd, buf, count);
}

MERCURY_POSIX_HANDLER_GEN_CALLBACK_STUB(hg_posix_write,
        hg_int64_t,
        (hg_int32_t), ,
        MERCURY_GEN_WITH_BULK, MERCURY_GEN_CONSUME_BULK
)

/* read */
MERCURY_POSIX_HANDLER_GEN_CALLBACK_STUB(read,
        hg_int64_t,
        (hg_int32_t), ,
        MERCURY_GEN_WITH_BULK, MERCURY_GEN_PRODUCE_BULK
)

static void
register_posix(void)
{
    MERCURY_POSIX_HANDLER_REGISTER(hg_posix_open1);
    MERCURY_POSIX_HANDLER_REGISTER(hg_posix_open2);
    MERCURY_POSIX_HANDLER_REGISTER(close);
    MERCURY_POSIX_HANDLER_REGISTER(hg_posix_write);
    MERCURY_POSIX_HANDLER_REGISTER(read);
}

/******************************************************************************/
int
main(int argc, char *argv[])
{
    na_class_t *network_class = NULL;
    unsigned int number_of_peers = 1;
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
