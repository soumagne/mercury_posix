/*
 * Copyright (C) 2013-2014 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#ifndef MERCURY_POSIX_PROC_H
#define MERCURY_POSIX_PROC_H

#include "mercury_posix_types.h"

#include <mercury_macros.h>
#include <mercury_proc_string.h>

/* Additional proc routines */
static HG_INLINE int
hg_proc_hg_long_t(hg_proc_t proc, hg_long_t *data)
{
    hg_int64_t converted_data;
    int ret;

    /* since we can't know if the size will be the same between systems,
     * assign to int64_t */
    if (hg_proc_get_op(proc) == HG_ENCODE) {
        converted_data = (hg_int64_t) *data;
    }

    ret = hg_proc_int64_t(proc, &converted_data);

    if (hg_proc_get_op(proc) == HG_DECODE) {
        *data = (hg_long_t) converted_data;
    }

    return ret;
}

static HG_INLINE int
hg_proc_hg_ulong_t(hg_proc_t proc, hg_ulong_t *data)
{
    hg_uint64_t converted_data;
    int ret;

    /* since we can't know if the size will be the same between systems,
     * assign to uint64_t */
    if (hg_proc_get_op(proc) == HG_ENCODE) {
        converted_data = (hg_uint64_t) *data;
    }

    ret = hg_proc_uint64_t(proc, &converted_data);

    if (hg_proc_get_op(proc) == HG_DECODE) {
        *data = (hg_ulong_t) converted_data;
    }

    return ret;
}

#define hg_proc_hg_size_t    hg_proc_hg_uint64_t
#define hg_proc_hg_ssize_t   hg_proc_hg_int64_t

#define hg_proc_hg_dev_t     hg_proc_hg_uint64_t
#define hg_proc_hg_uid_t     hg_proc_hg_uint32_t
#define hg_proc_hg_gid_t     hg_proc_hg_uint32_t

#ifdef HG_POSIX_HAS_OFF64_T
#define hg_proc_hg_ino_t     hg_proc_hg_uint64_t
#else
#define hg_proc_hg_ino_t     hg_proc_hg_ulong_t
#endif

#define hg_proc_hg_mode_t    hg_proc_hg_uint32_t

#ifdef __x86_64__
#define hg_proc_hg_nlink_t   hg_proc_hg_uint64_t
#else
#define hg_proc_hg_nlink_t   hg_proc_hg_uint32_t
#endif

#ifdef HG_POSIX_HAS_OFF64_T
#define hg_proc_hg_off_t     hg_proc_hg_int64_t
#else
#define hg_proc_hg_off_t     hg_proc_hg_long_t
#endif

#define hg_proc_hg_blksize_t hg_proc_hg_long_t

#ifdef HG_POSIX_HAS_OFF64_T
#define hg_proc_hg_blkcnt_t  hg_proc_hg_int64_t
#else
#define hg_proc_hg_blkcnt_t  hg_proc_hg_long_t
#endif

/* Proc routine for struct utimbuf */
MERCURY_GEN_STRUCT_PROC(hg_utimbuf_t,
        ((hg_long_t)(actime))
        ((hg_long_t)(modtime))
)

/* Proc routine for struct dirent */
MERCURY_GEN_PROC(hg_dirent_t,
        ((hg_ino_t)(d_ino))
        ((hg_off_t)(d_off))
        ((hg_uint16_t)(d_reclen))
        ((hg_uint8_t)(d_type))
        ((hg_string_t)(d_name))
)

/* Proc routine for stat structure */
#if defined __USE_MISC || defined __USE_XOPEN2K8
MERCURY_GEN_STRUCT_PROC(hg_stat_time_t,
        ((hg_long_t)(tv_sec))
        ((hg_long_t)(tv_nsec))
)
#else
#define hg_proc_hg_stat_time_t hg_proc_hg_long_t
#endif

MERCURY_GEN_STRUCT_PROC(hg_stat_t,
    ((hg_dev_t)(st_dev))              /* Device.  */
    ((hg_ino_t)(st_ino))              /* File serial number.  */
    ((hg_mode_t)(st_mode))            /* File mode.  */
    ((hg_nlink_t)(st_nlink))          /* Link count.  */
    ((hg_uid_t)(st_uid))              /* User ID of the file's owner. */
    ((hg_gid_t)(st_gid))              /* Group ID of the file's group.*/
    ((hg_dev_t)(st_rdev))             /* Device number, if device.  */
    ((hg_off_t)(st_size))             /* Size of file, in bytes.  */
    ((hg_blksize_t)(st_blksize))      /* Optimal block size for I/O.  */
    ((hg_blkcnt_t)(st_blocks))        /* Number 512-byte blocks allocated. */
    ((hg_stat_time_t)(st_atim))       /* Time of last access.  */
    ((hg_stat_time_t)(st_mtim))       /* Time of last modification.  */
    ((hg_stat_time_t)(st_ctim))       /* Time of last status change.  */
)

#endif /* MERCURY_POSIX_PROC_H */
