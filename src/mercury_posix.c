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

#include <stdarg.h>

/* 33 / 42 :) */

typedef hg_uint64_t hg_size_t;
typedef hg_int64_t  hg_ssize_t;
#define hg_proc_hg_size_t   hg_proc_hg_uint64_t
#define hg_proc_hg_ssize_t  hg_proc_hg_int64_t


typedef hg_uint64_t hg_dev_t;
typedef hg_uint32_t hg_uid_t;
typedef hg_uint32_t hg_gid_t;
typedef hg_uint64_t hg_ino_t;
/* ino64 ?*/
typedef hg_uint32_t hg_mode_t;
typedef hg_uint64_t hg_nlink_t;
typedef hg_int64_t  hg_off_t;

#define hg_proc_hg_dev_t  hg_proc_hg_uint64_t
#define hg_proc_hg_uid_t  hg_proc_hg_uint32_t
#define hg_proc_hg_gid_t  hg_proc_hg_uint32_t
#define hg_proc_hg_ino_t  hg_proc_hg_uint64_t
/* ino64 ?*/
#define hg_proc_hg_mode_t hg_proc_hg_uint32_t
#define hg_proc_hg_nlink_t  hg_proc_hg_uint64_t
#define hg_proc_hg_off_t  hg_proc_hg_int64_t

typedef struct stat hg_stat_t;

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

/* access */
MERCURY_POSIX_GEN_RPC_STUB(access,
        hg_int32_t,
        (hg_const_string_t)(hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* chdir */
MERCURY_POSIX_GEN_RPC_STUB(chdir,
        hg_int32_t,
        (hg_const_string_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* chmod */
MERCURY_POSIX_GEN_RPC_STUB(chmod,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* chown */
MERCURY_POSIX_GEN_RPC_STUB(chown,
        hg_int32_t,
        (hg_const_string_t)(hg_uid_t)(hg_gid_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* creat */
MERCURY_POSIX_GEN_RPC_STUB(creat,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* close */
MERCURY_POSIX_GEN_RPC_STUB(close,
        hg_int32_t,
        (hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* dup */
MERCURY_POSIX_GEN_RPC_STUB(dup,
        hg_int32_t,
        (hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* dup2 */
MERCURY_POSIX_GEN_RPC_STUB(dup2,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* dup3 */
MERCURY_POSIX_GEN_RPC_STUB(dup3,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t)(hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* fchdir */
MERCURY_POSIX_GEN_RPC_STUB(fchdir,
        hg_int32_t,
        (hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* fchmod */
MERCURY_POSIX_GEN_RPC_STUB(fchmod,
        hg_int32_t,
        (hg_int32_t)(hg_mode_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* fchown */
MERCURY_POSIX_GEN_RPC_STUB(fchown,
        hg_int32_t,
        (hg_int32_t)(hg_uid_t)(hg_gid_t), ,
        MERCURY_GEN_WITHOUT_BULK,
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
        (hg_int32_t)(hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* fstat */
MERCURY_POSIX_GEN_RPC_STUB(fstat,
        hg_int32_t,
        (hg_int32_t), (hg_stat_t),
        MERCURY_GEN_WITHOUT_BULK,
)

/* ftruncate */
MERCURY_POSIX_GEN_RPC_STUB(ftruncate,
        hg_int32_t,
        (hg_int32_t)(hg_off_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* getcwd */

//MERCURY_POSIX_GEN_RPC_STUB(getcwd,
//        hg_string_t,
//        (hg_string_t)(hg_size_t), ,
//        MERCURY_GEN_WITHOUT_BULK,
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
//MERCURY_GEN_PROC(get_current_dir_name_out_t, ((hg_string_t)(ret)))
//
//MERCURY_GEN_RPC_STUB(get_current_dir_name, hg_int32_t, -1, get_current_dir_name,
//        (void), ,
//        get_current_dir_name_out_t, ,
//        MERCURY_GEN_WITHOUT_BULK, )
//MERCURY_POSIX_GEN_RPC_STUB(get_current_dir_name,
//        hg_int32_t,
//        (void), ,
//        MERCURY_GEN_WITHOUT_BULK,
//)


char *
get_current_dir_name(void)
{
    HG_ERROR_DEFAULT("get_current_dir_name not implemented");
    return NULL;
}

/* lchown */
MERCURY_POSIX_GEN_RPC_STUB(lchown,
        hg_int32_t,
        (hg_const_string_t)(hg_uid_t)(hg_gid_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* link */
MERCURY_POSIX_GEN_RPC_STUB(link,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* lockf */
MERCURY_POSIX_GEN_RPC_STUB(lockf,
        hg_int32_t,
        (hg_int32_t)(hg_int32_t)(hg_off_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* lseek */
MERCURY_POSIX_GEN_RPC_STUB(lseek,
        hg_off_t,
        (hg_int32_t)(hg_off_t)(hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* lstat */
MERCURY_POSIX_GEN_RPC_STUB(lstat,
        hg_int32_t,
        (hg_const_string_t), (hg_stat_t),
        MERCURY_GEN_WITHOUT_BULK,
)

/* mkdir */
MERCURY_POSIX_GEN_RPC_STUB(mkdir,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* mkfifo */
MERCURY_POSIX_GEN_RPC_STUB(mkfifo,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* mknod */
MERCURY_POSIX_GEN_RPC_STUB(mknod,
        hg_int32_t,
        (hg_const_string_t)(hg_mode_t)(hg_dev_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/**
 * open
 */
MERCURY_POSIX_GEN_RPC_STUB(hg_posix_open1,
        hg_int32_t,
        (hg_const_string_t)(int32_t)(uint32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

MERCURY_POSIX_GEN_RPC_STUB(hg_posix_open2,
        hg_int32_t,
        (hg_const_string_t)(int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

int
open(const char *pathname, int flags, ...)
{
    va_list ap;
    int ret;

    va_start(ap, flags);
    if (flags & O_CREAT) {
        ret = hg_posix_open1(pathname, flags, va_arg(ap, mode_t));
    } else {
        ret = hg_posix_open2(pathname, flags);
    }
    va_end(ap);

    return ret;
}

/* pathconf */
MERCURY_POSIX_GEN_RPC_STUB(pathconf,
        hg_int64_t,
        (hg_const_string_t)(hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* pipe */
int
pipe(int fildes[2])
{
    HG_ERROR_DEFAULT("pipe not implemented");
    return -1;
}

/* read */
MERCURY_POSIX_GEN_RPC_STUB(read,
        hg_ssize_t,
        (int32_t), ,
        MERCURY_GEN_WITH_BULK, MERCURY_GEN_PRODUCE_BULK
)

/* rename */
MERCURY_POSIX_GEN_RPC_STUB(rename,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* rmdir */
MERCURY_POSIX_GEN_RPC_STUB(rmdir,
        hg_int32_t,
        (hg_const_string_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* stat */
MERCURY_POSIX_GEN_RPC_STUB(stat,
        hg_int32_t,
        (hg_const_string_t), (hg_stat_t),
        MERCURY_GEN_WITHOUT_BULK,
)

/* sync */
void
sync(void)
{
    HG_ERROR_DEFAULT("sync not implemented");
}

/* syncfs */
MERCURY_POSIX_GEN_RPC_STUB(syncfs,
        hg_int32_t,
        (hg_int32_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* symlink */
MERCURY_POSIX_GEN_RPC_STUB(symlink,
        hg_int32_t,
        (hg_const_string_t)(hg_const_string_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* truncate */
MERCURY_POSIX_GEN_RPC_STUB(truncate,
        hg_int32_t,
        (hg_const_string_t)(hg_off_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* umask */
MERCURY_POSIX_GEN_RPC_STUB(umask,
        hg_mode_t,
        (hg_mode_t), ,
        MERCURY_GEN_WITHOUT_BULK,
)

/* unlink */
MERCURY_POSIX_GEN_RPC_STUB(unlink,
        hg_int32_t,
        (hg_const_string_t), ,
        MERCURY_GEN_WITHOUT_BULK,
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
MERCURY_POSIX_GEN_RPC_STUB(hg_posix_write,
        hg_ssize_t,
        (int32_t), ,
        MERCURY_GEN_WITH_BULK, MERCURY_GEN_CONSUME_BULK
)

ssize_t
write(int fd, const void *buf, size_t count)
{
    return hg_posix_write(fd, (void*)buf, count);
}
