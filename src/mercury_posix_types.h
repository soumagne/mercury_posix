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

#include "mercury_posix_config.h"

#include <mercury_types.h>

#include <sys/stat.h>

typedef long          hg_long_t;
typedef unsigned long hg_ulong_t;

typedef hg_uint64_t hg_size_t;
typedef hg_int64_t  hg_ssize_t;

typedef hg_uint64_t hg_dev_t;
typedef hg_uint32_t hg_uid_t;
typedef hg_uint32_t hg_gid_t;

#ifdef HG_POSIX_HAS_OFF64_T
typedef hg_uint64_t hg_ino_t;
#else
typedef hg_ulong_t  hg_ino_t;
#endif

typedef hg_uint32_t hg_mode_t;

#ifdef __x86_64__
typedef hg_uint64_t  hg_nlink_t;
#else
typedef hg_uint32_t  hg_nlink_t;
#endif

#ifdef HG_POSIX_HAS_OFF64_T
typedef hg_int64_t  hg_off_t;
#else
typedef hg_long_t   hg_off_t;
#endif

typedef hg_long_t hg_blksize_t;

#ifdef HG_POSIX_HAS_OFF64_T
typedef hg_int64_t hg_blkcnt_t;
#else
typedef hg_long_t  hg_blkcnt_t;
#endif

typedef struct utimbuf hg_utimbuf_t;

#if defined __USE_MISC || defined __USE_XOPEN2K8
typedef struct timespec hg_stat_time_t;
#else
typedef hg_long_t hg_stat_time_t;
#endif

#ifdef HG_POSIX_HAS_STAT64
typedef struct stat64 hg_stat_t;
#else
typedef struct stat hg_stat_t;
#endif

#endif /* MERCURY_POSIX_TYPES_H */
