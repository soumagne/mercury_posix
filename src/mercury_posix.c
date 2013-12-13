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
#include "mercury_util/mercury_list.h"

#include <stdarg.h>
#define __USE_GNU
#include <dlfcn.h>

#define REAL_DECL(name,ret,args) \
ret (*__real_ ## name)args = NULL;

#define GET_REAL_DECL(func) \
        if (!(__real_ ## func)) \
        { \
            __real_ ## func = dlsym(RTLD_NEXT, #func); \
        }

static hg_list_entry_t *hg_posix_fd_list_g = NULL;
static HG_INLINE int
hg_posix_fd_equal(hg_list_value_t value1, hg_list_value_t value2)
{
    return *((int*)value1) == *((int*)value2);
}

static HG_INLINE void
hg_posix_store_fd(int fd)
{
    int *fd_buf = (int *) malloc(sizeof(int));
    *fd_buf = fd;
    if (!hg_list_find_data(hg_posix_fd_list_g, hg_posix_fd_equal,
            (hg_list_value_t)fd_buf)) {
        if (!hg_list_append(&hg_posix_fd_list_g, (hg_list_value_t)fd_buf)) {
            HG_ERROR_DEFAULT("Could not append handle to list");
        }
    }
}

static HG_INLINE hg_bool_t
hg_posix_check_fd(int fd)
{
    hg_bool_t ret = 1;

    ret = (hg_list_find_data(hg_posix_fd_list_g, hg_posix_fd_equal,
            (hg_list_value_t)&fd) != NULL);

    return ret;
}

static HG_INLINE void
hg_posix_remove_fd(int fd)
{
    hg_list_entry_t *fd_buf_entry = hg_list_find_data(hg_posix_fd_list_g,
            hg_posix_fd_equal, (hg_list_value_t)&fd);
    int *fd_buf = hg_list_data(fd_buf_entry);
    hg_list_remove_data(&hg_posix_fd_list_g, hg_posix_fd_equal,
            (hg_list_value_t)&fd);
    free(fd_buf);
}

/* Only routines that can't automatically be generated are defined here */

/**
 * close
 */
REAL_DECL(close, int, (int));
int
close(int fd)
{
    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(close);
        return __real_close(fd);
    }
    hg_posix_remove_fd(fd);
    return hg_posix_close(fd);
}

/**
 * closedir
 */
int
closedir(DIR *dirp)
{
    return hg_posix_closedir((hg_ptr_t)dirp);
}

/**
 * getcwd
 */
char *
getcwd(char *buf, size_t size)
{
    getcwd_in_t in_struct;
    getcwd_out_t out_struct;
    char *ret;
    na_class_t *network_class;
    char *server_name;
    na_addr_t addr;
    hg_id_t id;

    hg_request_t request;
    hg_status_t status;
    hg_bool_t hg_initialized;

    hg_bool_t func_registered;
    int hg_ret, na_ret;

    /* Is mercury library initialized */
    HG_Initialized(&hg_initialized, &network_class);
    if (!hg_initialized) {
        network_class = NA_Initialize(getenv(HG_PORT_NAME), 0);

        hg_ret = HG_Init(network_class);
        if (hg_ret != HG_SUCCESS) {
            HG_ERROR_DEFAULT("Could not initialize function shipper");
            ret = NULL;
            goto done;
        }
    }

    /* Get server_name if set */
    server_name = getenv(HG_PORT_NAME);
    /* Look up addr id */
    na_ret = NA_Addr_lookup(network_class, server_name, &addr);
    if (na_ret != NA_SUCCESS) {
        HG_ERROR_DEFAULT("Could not lookup addr");
        ret = NULL;
        goto done;
    }

    /* Check whether call has already been registered or not */
    HG_Registered("getcwd", &func_registered, &id);
    if (!func_registered) {
        id = MERCURY_REGISTER("getcwd", getcwd_in_t, getcwd_out_t);
    }

    /* Fill input structure */
    in_struct.size = size;

    /* Forward call to remote addr and get a new request */
    hg_ret = HG_Forward(addr, id, &in_struct, &out_struct, &request);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Could not forward call");
        ret = NULL;
        goto done;
    }

    /* Wait for call to be executed and return value to be sent back
     * (Request is freed when the call completes)
     */
    hg_ret = HG_Wait(request, HG_MAX_IDLE_TIME, &status);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Error during wait");
        ret = NULL;
        goto done;
    }
    if (!status) {
        HG_ERROR_DEFAULT("Operation did not complete");
        ret = NULL;
        goto done;
    }

    /* Get output parameters */
    strcpy(buf, out_struct.string_out);
    ret = buf;

    /* Free request */
    hg_ret = HG_Request_free(request);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Could not free request");
        ret = NULL;
        goto done;
    }

done:
    return ret;
}

/**
 * open
 */
#ifndef HG_POSIX_HAS_OPEN64
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

    /* Keep track of fd */
    hg_posix_store_fd(ret);

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

    /* Keep track of fd */
    hg_posix_store_fd(ret);

    return ret;
}
#endif

/**
 * opendir
 */
DIR *
opendir(const char *dirname)
{
    return (DIR*)hg_posix_opendir(dirname);
}

/**
 * pipe
 */
int
pipe(int fildes[2])
{
    /* TODO A very clean implementation would require an additional mercury proc
     * that encodes and decodes an array of count types. Here we have only
     * two integers so it is simpler like this for now. */
    return hg_posix_pipe(fildes[0], fildes[1]);
}

/**
 * pread
 * TODO for now for convenience just map to our own posix_pread prototype
 */
#ifndef HG_POSIX_HAS_PREAD64
ssize_t
pread(int fd, void *buf, size_t count, off_t offset)
{
    return hg_posix_pread(fd, offset, buf, count);
}
#else
ssize_t
pread64(int fd, void *buf, size_t count, off_t offset)
{
    return hg_posix_pread64(fd, offset, buf, count);
}
#endif

/**
 * pwrite
 * TODO for now for convenience just map to our own posix_pwrite prototype
 */
#ifndef HG_POSIX_HAS_PWRITE64
ssize_t
pwrite(int fd, const void *buf, size_t count, off_t offset)
{
    return hg_posix_pwrite(fd, offset, (void*)buf, count);
}
#else
ssize_t
pwrite64(int fd, const void *buf, size_t count, off_t offset)
{
    return hg_posix_pwrite64(fd, offset, (void*)buf, count);
}
#endif

/**
 * read
 */
REAL_DECL(read, ssize_t, (int, void*, size_t));
ssize_t
read(int fd, void *buf, size_t count)
{
    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(read);
        return __real_read(fd, buf, count);
    }
    return hg_posix_read(fd, buf, count);
}

/**
 * readdir
 */
static struct dirent *
hg_posix_readdir(DIR *dirp)
{
    readdir_in_t in_struct;
    readdir_out_t out_struct;
    static struct dirent dirent_ret;
    struct dirent *ret;
    na_class_t *network_class;
    char *server_name;
    na_addr_t addr;
    hg_id_t id;

    hg_request_t request;
    hg_status_t status;
    hg_bool_t hg_initialized;

    hg_bool_t func_registered;
    int hg_ret, na_ret;

    /* Is mercury library initialized */
    HG_Initialized(&hg_initialized, &network_class);
    if (!hg_initialized) {
        network_class = NA_Initialize(getenv(HG_PORT_NAME), 0);

        hg_ret = HG_Init(network_class);
        if (hg_ret != HG_SUCCESS) {
            HG_ERROR_DEFAULT("Could not initialize function shipper");
            ret = NULL;
            goto done;
        }
    }

    /* Get server_name if set */
    server_name = getenv(HG_PORT_NAME);
    /* Look up addr id */
    na_ret = NA_Addr_lookup(network_class, server_name, &addr);
    if (na_ret != NA_SUCCESS) {
        HG_ERROR_DEFAULT("Could not lookup addr");
        ret = NULL;
        goto done;
    }

    /* Check whether call has already been registered or not */
    HG_Registered("readdir", &func_registered, &id);
    if (!func_registered) {
        id = MERCURY_REGISTER("readdir", getcwd_in_t, getcwd_out_t);
    }

    /* Fill input structure */
    in_struct.dirp = (hg_ptr_t)dirp;

    /* Forward call to remote addr and get a new request */
    hg_ret = HG_Forward(addr, id, &in_struct, &out_struct, &request);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Could not forward call");
        ret = NULL;
        goto done;
    }

    /* Wait for call to be executed and return value to be sent back
     * (Request is freed when the call completes)
     */
    hg_ret = HG_Wait(request, HG_MAX_IDLE_TIME, &status);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Error during wait");
        ret = NULL;
        goto done;
    }
    if (!status) {
        HG_ERROR_DEFAULT("Operation did not complete");
        ret = NULL;
        goto done;
    }

    /* Get output parameters */
    dirent_ret.d_ino = out_struct.dirent_out.d_ino;
    dirent_ret.d_off = out_struct.dirent_out.d_off;
    dirent_ret.d_reclen = out_struct.dirent_out.d_reclen;
    dirent_ret.d_type = out_struct.dirent_out.d_type;
    strcpy(dirent_ret.d_name, out_struct.dirent_out.d_name);

    /* Free request */
    hg_ret = HG_Request_free(request);
    if (hg_ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Could not free request");
        ret = NULL;
        goto done;
    }

    ret = &dirent_ret;

done:
    return ret;
}

#ifndef HG_POSIX_HAS_READDIR64
struct dirent *
readdir(DIR *dirp)
{
    return hg_posix_readdir(dirp);
}
#else
struct dirent64 *
readdir64(DIR *dirp)
{
    return (struct dirent64 *) hg_posix_readdir(dirp);
}
#endif


/**
 * rewinddir
 */
void
rewinddir(DIR *dirp)
{
    (void) hg_posix_rewinddir((hg_ptr_t)dirp);
}

/**
 * write
 */
REAL_DECL(write, int, (int, const void *, size_t));
ssize_t
write(int fd, const void *buf, size_t count)
{
    if (!hg_posix_check_fd(fd)) {
        GET_REAL_DECL(write);
        return __real_write(fd, buf, count);
    }
    return hg_posix_write(fd, (void*)buf, count);
}

/**
 * utime
 */
int
utime(const char *path, const struct utimbuf *times)
{
    hg_utimbuf_t hg_utimbuf_times;

    hg_utimbuf_times.actime = times->actime;
    hg_utimbuf_times.modtime = times->modtime;

    return hg_posix_utime(path, hg_utimbuf_times);
}
