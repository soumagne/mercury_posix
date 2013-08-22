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
#include "mercury_posix_macros.h"
#include "mercury_posix_proc.h"

#include <stdarg.h>

/* 33 / 42 :) */

/* access */
//MERCURY_POSIX_GEN_RPC_STUB(access,
//        hg_int32_t,
//        (hg_const_string_t)(hg_int32_t),
//)

/* chdir */
//MERCURY_POSIX_GEN_RPC_STUB(chdir,
//        hg_int32_t,
//        (hg_const_string_t),
//)

/* chmod */
MERCURY_POSIX_GEN_RPC_STUB(chmod,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)

/* chown */
MERCURY_POSIX_GEN_RPC_STUB(chown,
        hg_int32_t,
        (hg_const_string_t)(hg_uid_t)(hg_gid_t),
)

/* creat */
MERCURY_POSIX_GEN_RPC_STUB(creat,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)

/* close */
MERCURY_POSIX_GEN_RPC_STUB(close,
        hg_int32_t,
        (hg_int32_t),
)

/* dup */
MERCURY_POSIX_GEN_RPC_STUB(dup,
        hg_int32_t,
        (hg_int32_t),
)

/* dup2 */
MERCURY_POSIX_GEN_RPC_STUB(dup2,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t),
)

/* dup3 */
//MERCURY_POSIX_GEN_RPC_STUB(dup3,
//        hg_int32_t,
//        (hg_int32_t)(hg_int32_t)(hg_int32_t),
//)

/* fchdir */
MERCURY_POSIX_GEN_RPC_STUB(fchdir,
        hg_int32_t,
        (hg_int32_t),
)

/* fchmod */
MERCURY_POSIX_GEN_RPC_STUB(fchmod,
        hg_int32_t,
        (hg_int32_t)(hg_mode_t),
)

/* fchown */
MERCURY_POSIX_GEN_RPC_STUB(fchown,
        hg_int32_t,
        (hg_int32_t)(hg_uid_t)(hg_gid_t),
)

/**
 * fcntl
 */
/*
int
fcntl(int fd, int cmd, ...)
{
    HG_ERROR_DEFAULT("fcntl not implemented");
    return -1;
}
*/

/* fpathconf */
MERCURY_POSIX_GEN_RPC_STUB(fpathconf,
        hg_int64_t,
        (hg_int32_t)(hg_int32_t),
)

/* fstat */
MERCURY_POSIX_GEN_RPC_STUB(fstat,
        hg_int32_t,
        (hg_int32_t), (hg_stat_t)
)

/* ftruncate */
MERCURY_POSIX_GEN_RPC_STUB(ftruncate,
        hg_int32_t,
        (hg_int32_t)(hg_off_t),
)

/* getcwd */

//MERCURY_POSIX_GEN_RPC_STUB(getcwd,
//        hg_string_t,
//        (hg_string_t)(hg_size_t), ,
//        MERCURY_GEN_FALSE,
//)
//
//char *
//getcwd(char *buf, size_t size)
//{
//    char *ret;
//
//    hg_getcwd(buf, size, &ret);
//    return ret;
//}

/* getwd */
char *
getwd(char *buf)
{
    HG_ERROR_DEFAULT("getwd not implemented");
    return NULL;
}

/* get_current_dir_name */
MERCURY_GEN_PROC(get_current_dir_name_out_t, HG_GEN_RET_PARAM(hg_string_t))
MERCURY_GEN_RPC_STUB(get_current_dir_name, get_current_dir_name,
        MERCURY_GEN_TRUE, hg_string_t, NULL,
        MERCURY_GEN_FALSE, , ,
        MERCURY_GEN_FALSE, get_current_dir_name_out_t, ,
        MERCURY_GEN_FALSE, )

/* lchown */
MERCURY_POSIX_GEN_RPC_STUB(lchown,
        hg_int32_t,
        (hg_const_string_t)(hg_uid_t)(hg_gid_t),
)

/* link */
MERCURY_POSIX_GEN_RPC_STUB(link,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t),
)

/* lockf */
MERCURY_POSIX_GEN_RPC_STUB(lockf,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t)(hg_off_t),
)

/* lseek */
MERCURY_POSIX_GEN_RPC_STUB(lseek,
        hg_off_t,
        (hg_int32_t)(hg_off_t)(hg_int32_t),
)

/* lstat */
MERCURY_POSIX_GEN_RPC_STUB(lstat,
        hg_int32_t,
        (hg_const_string_t), (hg_stat_t)
)

/* mkdir */
MERCURY_POSIX_GEN_RPC_STUB(mkdir,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)

/* mkfifo */
MERCURY_POSIX_GEN_RPC_STUB(mkfifo,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)

/* mknod */
MERCURY_POSIX_GEN_RPC_STUB(mknod,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t)(hg_dev_t),
)

/**
 * open
 */
#define open_in_params ((hg_const_string_t)(pathname))((hg_int32_t)(flags))((hg_uint32_t)(mode))

HG_GEN_STRUCT(open_in_t, open_in_params)

static HG_INLINE int
hg_proc_open_in_t(hg_proc_t proc, void *data)
{
    open_in_t *struct_data = (open_in_t *) data;
    hg_proc_hg_const_string_t(proc, &struct_data->pathname);
    hg_proc_hg_int32_t(proc, &struct_data->flags);
    if (struct_data->flags & O_CREAT) {
        hg_proc_hg_uint32_t(proc, &struct_data->mode);
    }
    return 1;
}

MERCURY_GEN_PROC(open_out_t, ((hg_int32_t)(ret)))
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

/* pathconf */
MERCURY_POSIX_GEN_RPC_STUB(pathconf,
        hg_int64_t,
        (hg_const_string_t)(hg_int32_t),
)

/* pipe */
int
pipe(int fildes[2])
{
    HG_ERROR_DEFAULT("pipe not implemented");
    return -1;
}

/* read */
MERCURY_POSIX_GEN_RPC_BULK_STUB(read,
        hg_ssize_t,
        (int32_t),
        ,
        MERCURY_GEN_FALSE
)

/* rename */
MERCURY_POSIX_GEN_RPC_STUB(rename,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t),
)

/* rmdir */
MERCURY_POSIX_GEN_RPC_STUB(rmdir,
        hg_int32_t,
        (hg_const_string_t),
)

/* stat */
MERCURY_POSIX_GEN_RPC_STUB(stat,
        hg_int32_t,
        (hg_const_string_t), (hg_stat_t)
)

/* sync */
MERCURY_POSIX_GEN_RPC_STUB_NOINPUT_NORET(sync)

/* syncfs */
//MERCURY_POSIX_GEN_RPC_STUB(syncfs,
//        hg_int32_t,
//        (hg_int32_t),
//)

/* symlink */
MERCURY_POSIX_GEN_RPC_STUB(symlink,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t),
)

/* truncate */
MERCURY_POSIX_GEN_RPC_STUB(truncate,
        hg_int32_t,
        (hg_const_string_t)(hg_off_t),
)

/* umask */
MERCURY_POSIX_GEN_RPC_STUB(umask,
        hg_mode_t,
        (hg_mode_t),
)

/* unlink */
MERCURY_POSIX_GEN_RPC_STUB(unlink,
        hg_int32_t,
        (hg_const_string_t),
)

/* utime */
int
utime(const char *path, const struct utimbuf *times)
{
    HG_ERROR_DEFAULT("utime not implemented");
    return -1;
}

/**
 * write
 */
MERCURY_POSIX_GEN_RPC_BULK_STUB(hg_posix_write,
        hg_ssize_t,
        (int32_t), ,
        MERCURY_GEN_TRUE
)

ssize_t
write(int fd, const void *buf, size_t count)
{
    return hg_posix_write(fd, (void*)buf, count);
}
