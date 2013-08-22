/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
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

#define hg_proc_hg_size_t    hg_proc_hg_uint64_t
#define hg_proc_hg_ssize_t   hg_proc_hg_int64_t

#define hg_proc_hg_dev_t     hg_proc_hg_uint64_t
#define hg_proc_hg_uid_t     hg_proc_hg_uint32_t
#define hg_proc_hg_gid_t     hg_proc_hg_uint32_t
#define hg_proc_hg_ino_t     hg_proc_hg_uint64_t
/* ino64 ?*/
#define hg_proc_hg_mode_t    hg_proc_hg_uint32_t
#define hg_proc_hg_nlink_t   hg_proc_hg_uint64_t
#define hg_proc_hg_off_t     hg_proc_hg_int64_t

#define hg_proc_hg_blksize_t hg_proc_hg_int64_t
#define hg_proc_hg_blkcnt_t  hg_proc_hg_int64_t

/* open */
//#define open_in_params ((hg_string_t)(pathname))((hg_int32_t)(flags))((hg_uint32_t)(mode))
//
//HG_GEN_STRUCT(open_in_t, open_in_params)
//static HG_INLINE int
//hg_proc_open_in_t(hg_proc_t proc, void *data)
//{
//    open_in_t *struct_data = (open_in_t *) data;
//    hg_proc_hg_string_t(proc, &struct_data->pathname);
//    hg_proc_hg_int32_t(proc, &struct_data->flags);
//    if (struct_data->flags & O_CREAT) {
//        hg_proc_hg_uint32_t(proc, &struct_data->mode);
//    }
//    return 1;
//}
//MERCURY_GEN_PROC(open_out_t, ((hg_int32_t)(ret)))

/* stat */
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
//    ((hg_time_t)(st_atim))        /* Time of last access.  */
//    ((hg_time_t)(st_mtim))        /* Time of last modification.  */
//    ((hg_time_t)(st_ctim))        /* Time of last status change.  */
)


#endif /* MERCURY_POSIX_PROC_H */
