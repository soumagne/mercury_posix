/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#ifndef MERCURY_POSIX_GEN_H
#define MERCURY_POSIX_GEN_H

#include "mercury_posix_macros.h"
#include "mercury_posix_proc.h"

/* access */
MERCURY_POSIX_GEN_STUB(access,
        hg_int32_t,
        (hg_const_string_t)(hg_int32_t),
)

/* chdir */
/*
MERCURY_POSIX_GEN_STUB(chdir,
        hg_int32_t,
        (hg_const_string_t),
)
*/

/* chmod */
MERCURY_POSIX_GEN_STUB(chmod,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)

/* chown */
MERCURY_POSIX_GEN_STUB(chown,
        hg_int32_t,
        (hg_const_string_t)(hg_uid_t)(hg_gid_t),
)

/* creat */
#ifndef HG_POSIX_HAS_CREAT64
MERCURY_POSIX_GEN_STUB(creat,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)
#else
MERCURY_POSIX_GEN_STUB(creat64,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)
#endif

/* close */
MERCURY_POSIX_GEN_STUB(close,
        hg_int32_t,
        (hg_int32_t),
)

/* closedir */
MERCURY_POSIX_GEN_STUB(closedir,
        hg_int32_t,
        (hg_ptr_t),
)

/* dup */
MERCURY_POSIX_GEN_STUB(dup,
        hg_int32_t,
        (hg_int32_t),
)

/* dup2 */
MERCURY_POSIX_GEN_STUB(dup2,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t),
)

/* fchdir */
MERCURY_POSIX_GEN_STUB(fchdir,
        hg_int32_t,
        (hg_int32_t),
)

/* fchmod */
MERCURY_POSIX_GEN_STUB(fchmod,
        hg_int32_t,
        (hg_int32_t)(hg_mode_t),
)

/* fchown */
MERCURY_POSIX_GEN_STUB(fchown,
        hg_int32_t,
        (hg_int32_t)(hg_uid_t)(hg_gid_t),
)

/**
 * fcntl
 */

/* fdatasync */
MERCURY_POSIX_GEN_STUB(fdatasync,
        hg_int32_t,
        (hg_int32_t),
)

/* fpathconf */
MERCURY_POSIX_GEN_STUB(fpathconf,
        hg_long_t,
        (hg_int32_t)(hg_int32_t),
)

/* fsync */
MERCURY_POSIX_GEN_STUB(fsync,
        hg_int32_t,
        (hg_int32_t),
)

/* ftruncate */
#ifndef HG_POSIX_HAS_FTRUNCATE64
MERCURY_POSIX_GEN_STUB(ftruncate,
        hg_int32_t,
        (hg_int32_t)(hg_off_t),
)
#else
MERCURY_POSIX_GEN_STUB(ftruncate64,
        hg_int32_t,
        (hg_int32_t)(hg_off_t),
)
#endif

/* getcwd */
MERCURY_GEN_PROC(getcwd_in_t, ((hg_uint64_t)(size)))
MERCURY_GEN_PROC(getcwd_out_t, ((hg_string_t)(string_out)))

/* lchown */
MERCURY_POSIX_GEN_STUB(lchown,
        hg_int32_t,
        (hg_const_string_t)(hg_uid_t)(hg_gid_t),
)

/* link */
MERCURY_POSIX_GEN_STUB(link,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t),
)

/* lockf */
MERCURY_POSIX_GEN_STUB(lockf,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t)(hg_off_t),
)

/* lseek */
#ifndef HG_POSIX_HAS_LSEEK64
MERCURY_POSIX_GEN_STUB(lseek,
        hg_off_t,
        (hg_int32_t)(hg_off_t)(hg_int32_t),
)
#else
MERCURY_POSIX_GEN_STUB(lseek64,
        hg_off_t,
        (hg_int32_t)(hg_off_t)(hg_int32_t),
)
#endif

/* mkdir */
MERCURY_POSIX_GEN_STUB(mkdir,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)

/* mkfifo */
MERCURY_POSIX_GEN_STUB(mkfifo,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t),
)

/* mknod */
MERCURY_POSIX_GEN_STUB(mknod,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t)(hg_dev_t),
)

/**
 * open
 */
/* TODO may be simplified */
#define open_in_params ((hg_const_string_t)(pathname))((hg_int32_t)(flags))((hg_uint32_t)(mode))

HG_GEN_STRUCT(open_in_t, open_in_params)

static HG_INLINE int
hg_proc_open_in_t(hg_proc_t proc, void *data)
{
    int ret = HG_SUCCESS;
    open_in_t *struct_data = (open_in_t *) data;

    ret = hg_proc_hg_const_string_t(proc, &struct_data->pathname);
    if (ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Proc error");
        return ret;
    }
    ret = hg_proc_hg_int32_t(proc, &struct_data->flags);
    if (ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Proc error");
        return ret;
    }
    if (struct_data->flags & O_CREAT) {
        ret = hg_proc_hg_uint32_t(proc, &struct_data->mode);
        if (ret != HG_SUCCESS) {
            HG_ERROR_DEFAULT("Proc error");
            return ret;
        }
    }
    return ret;
}

MERCURY_GEN_PROC(open_out_t, ((hg_int32_t)(ret)))

/* opendir */
MERCURY_POSIX_GEN_STUB(opendir,
        hg_ptr_t,
        (hg_const_string_t),
)

/* pathconf */
MERCURY_POSIX_GEN_STUB(pathconf,
        hg_long_t,
        (hg_const_string_t)(hg_int32_t),
)

/* pipe */
MERCURY_POSIX_GEN_STUB(pipe,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t),
)

/* pread */
#ifndef HG_POSIX_HAS_PREAD64
MERCURY_POSIX_GEN_BULK_STUB(pread,
        hg_ssize_t,
        (int32_t)(hg_off_t),
        ,
        MERCURY_GEN_FALSE
)
#else
MERCURY_POSIX_GEN_BULK_STUB(pread64,
        hg_ssize_t,
        (int32_t)(hg_off_t),
        ,
        MERCURY_GEN_FALSE
)
#endif

/* pwrite */
#ifndef HG_POSIX_HAS_PWRITE64
MERCURY_POSIX_GEN_BULK_STUB(pwrite,
        hg_ssize_t,
        (int32_t)(hg_off_t),
        ,
        MERCURY_GEN_TRUE
)
#else
MERCURY_POSIX_GEN_BULK_STUB(pwrite64,
        hg_ssize_t,
        (int32_t)(hg_off_t),
        ,
        MERCURY_GEN_TRUE
)
#endif

/* read */
MERCURY_POSIX_GEN_BULK_STUB(read,
        hg_ssize_t,
        (int32_t),
        ,
        MERCURY_GEN_FALSE
)

/* readdir */
MERCURY_GEN_PROC(readdir_in_t, ((hg_ptr_t)(dirp)))
MERCURY_GEN_PROC(readdir_out_t, ((hg_dirent_t)(dirent_out)))

/* rename */
MERCURY_POSIX_GEN_STUB(rename,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t),
)

/* rewinddir */
MERCURY_POSIX_GEN_STUB(rewinddir,
        hg_uint8_t,
        (hg_ptr_t),
)

/* rmdir */
MERCURY_POSIX_GEN_STUB(rmdir,
        hg_int32_t,
        (hg_const_string_t),
)

/* sync */
MERCURY_POSIX_GEN_STUB_NOINPUT_NORET(sync)

/* symlink */
MERCURY_POSIX_GEN_STUB(symlink,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t),
)

/* truncate */
#ifndef HG_POSIX_HAS_TRUNCATE64
MERCURY_POSIX_GEN_STUB(truncate,
        hg_int32_t,
        (hg_const_string_t)(hg_off_t),
)
#else
MERCURY_POSIX_GEN_STUB(truncate64,
        hg_int32_t,
        (hg_const_string_t)(hg_off_t),
)
#endif

/* umask */
MERCURY_POSIX_GEN_STUB(umask,
        hg_mode_t,
        (hg_mode_t),
)

/* unlink */
MERCURY_POSIX_GEN_STUB(unlink,
        hg_int32_t,
        (hg_const_string_t),
)

/* utime */
MERCURY_POSIX_GEN_STUB(utime,
        hg_int32_t,
        (hg_const_string_t)(hg_utimbuf_t),
)

/**
 * write
 */
MERCURY_POSIX_GEN_BULK_STUB(write,
        hg_ssize_t,
        (int32_t), ,
        MERCURY_GEN_TRUE
)

/* stat wrappers */
#ifndef HG_POSIX_HAS_FSTAT64
MERCURY_POSIX_GEN_STUB(__fxstat,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t), (hg_stat_t)
)
#else
MERCURY_POSIX_GEN_STUB(__fxstat64,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t), (hg_stat_t)
)
#endif

#ifndef HG_POSIX_HAS_STAT64
MERCURY_POSIX_GEN_STUB(__xstat,
        hg_int32_t,
        (hg_int32_t)(hg_const_string_t), (hg_stat_t)
)
#else
MERCURY_POSIX_GEN_STUB(__xstat64,
        hg_int32_t,
        (hg_int32_t)(hg_const_string_t), (hg_stat_t)
)
#endif

#ifndef HG_POSIX_HAS_LSTAT64
MERCURY_POSIX_GEN_STUB(__lxstat,
        hg_int32_t,
        (hg_int32_t)(hg_const_string_t), (hg_stat_t)
)
#else
MERCURY_POSIX_GEN_STUB(__lxstat64,
        hg_int32_t,
        (hg_int32_t)(hg_const_string_t), (hg_stat_t)
)
#endif

#endif /* MERCURY_POSIX_GEN_H */
