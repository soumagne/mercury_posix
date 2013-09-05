/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#include "mercury_posix.h"
#include "mercury_posix_gen.h"

#include <stdarg.h>

/* getcwd */
//MERCURY_POSIX_GEN_RPC_STUB(getcwd,
//        hg_string_t,
//        (hg_string_t)(hg_size_t), ,
//        MERCURY_GEN_FALSE,
//)
char *
getcwd(char *buf, size_t size)
{
    HG_ERROR_DEFAULT("getcwd not implemented");
    return NULL;
}

/* getwd */
char *
getwd(char *buf)
{
    HG_ERROR_DEFAULT("getwd not implemented");
    return NULL;
}

/* get_current_dir_name */
//MERCURY_GEN_PROC(get_current_dir_name_out_t, HG_GEN_RET_PARAM(hg_string_t))
//MERCURY_GEN_RPC_STUB(get_current_dir_name, get_current_dir_name,
//        MERCURY_GEN_TRUE, hg_string_t, NULL,
//        MERCURY_GEN_FALSE, , ,
//        MERCURY_GEN_FALSE, get_current_dir_name_out_t, ,
//        MERCURY_GEN_FALSE, )
char *
get_current_dir_name(void)
{
    HG_ERROR_DEFAULT("get_current_dir_name not implemented");
    return NULL;
}

/**
 * open
 */
#ifndef HG_POSIX_HAS_LARGE_FILE
MERCURY_GEN_RPC_STUB(hg_posix_open, open,
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

    return ret;
}
#else
MERCURY_GEN_RPC_STUB(hg_posix_open64, open64,
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

    return ret;
}
#endif

/**
 * write
 */
ssize_t
write(int fd, const void *buf, size_t count)
{
    return hg_posix_write(fd, (void*)buf, count);
}
