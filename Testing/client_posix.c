/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#include "mercury_posix_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/******************************************************************************/
int main(int argc, char *argv[])
{
    int ret;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    char filename[256];
    int fd = 0;
    int *read_buf = NULL;
    int *write_buf = NULL;
    size_t n_ints = 1024*1024;
    unsigned int i;
    int error = 0;
    int rank = 0;
    ssize_t nbyte;
    (void) argc;
    (void) argv;

    sprintf(filename, "posix_test%d", rank);

    /* Prepare buffers */
    write_buf = malloc(sizeof(int) * n_ints);
    read_buf =  malloc(sizeof(int) * n_ints);
    for (i = 0; i < n_ints; i++) {
        write_buf[i] = i;
        read_buf[i] = 0;
    }

    printf("(%d) Creating file...\n", rank);

#ifdef HG_POSIX_HAS_OPEN64
    fd = open64(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
#else
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
#endif
    if (fd < 0) {
        fprintf(stderr, "Error in fs_open\n");
        return EXIT_FAILURE;
    }

    printf("(%d) Writing data...\n", rank);

    nbyte = write(fd, write_buf, sizeof(int) * n_ints);
    if (nbyte <= 0) {
        fprintf(stderr, "Error detected in client_posix_write\n");
        return EXIT_FAILURE;
    }

    printf("(%d) Closing file...\n", rank);

    ret = close(fd);
    if (ret < 0) {
        fprintf(stderr, "Error detected in client_posix_close\n");
        return EXIT_FAILURE;
    }

    printf("(%d) Opening file...\n", rank);

#ifdef HG_POSIX_HAS_OPEN64
    fd = open64(filename, O_RDONLY, mode);
#else
    fd = open(filename, O_RDONLY, mode);
#endif
    if (fd < 0) {
        fprintf(stderr, "Error in fs_open\n");
        return EXIT_FAILURE;
    }

    printf("(%d) Reading data...\n", rank);

    nbyte = read(fd, read_buf, sizeof(int) * n_ints);
    if (nbyte < 0) {
        fprintf(stderr, "Error detected in client_posix_read\n");
        return EXIT_FAILURE;
    }

    printf("(%d) Closing file...\n", rank);

    ret = close(fd);
    if (ret < 0) {
        fprintf(stderr, "Error detected in client_posix_close\n");
        return EXIT_FAILURE;
    }

    printf("(%d) Checking data...\n", rank);

    /* Check bulk buf */
    for (i = 0; i < n_ints; i++) {
        if (read_buf[i] != write_buf[i]) {
            printf("(%d) Error detected in bulk transfer, read_buf[%d] = %d, was expecting %d!\n",
                    rank, i, read_buf[i], write_buf[i]);
            error = 1;
            break;
        }
    }
    if (!error) printf("(%d) Successfully written %lu bytes!\n", rank, nbyte);

    /* Free bulk data */
    free(write_buf);
    free(read_buf);

    return EXIT_SUCCESS;
}
