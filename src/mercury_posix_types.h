/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#ifndef MERCURY_POSIX_TYPES_H
#define MERCURY_POSIX_TYPES_H

#include <mercury_types.h>

#include <sys/stat.h>

typedef hg_uint64_t hg_size_t;
typedef hg_int64_t  hg_ssize_t;

typedef hg_uint64_t hg_dev_t;
typedef hg_uint32_t hg_uid_t;
typedef hg_uint32_t hg_gid_t;
typedef hg_uint64_t hg_ino_t;
/* ino64 ?*/
typedef hg_uint32_t hg_mode_t;
typedef hg_uint64_t hg_nlink_t;
typedef hg_int64_t  hg_off_t;

typedef hg_int64_t hg_blksize_t;
typedef hg_int64_t hg_blkcnt_t;

typedef struct stat hg_stat_t;

#endif /* MERCURY_POSIX_TYPES_H */
