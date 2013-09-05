/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#ifndef MERCURY_POSIX_MACROS_H
#define MERCURY_POSIX_MACROS_H

#include <mercury_macros.h>

/*****************************************************************************
 * High-level BOOST macros for client/server stub generation
 *****************************************************************************/
#define MERCURY_POSIX_GEN_CALLBACK_STUB(func_name, ret_type, in_types, out_types) \
        MERCURY_HANDLER_GEN_CALLBACK_STUB(BOOST_PP_CAT(func_name, _cb), func_name, \
                MERCURY_GEN_TRUE, ret_type, \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _in_t), HG_GEN_PARAM_NAME_SEQ(in_param_, in_types), \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _out_t), HG_GEN_PARAM_NAME_SEQ(out_param_, out_types), \
                MERCURY_GEN_FALSE, )

#define MERCURY_POSIX_GEN_RPC_STUB(func_name, ret_type, in_types, out_types) \
        MERCURY_GEN_RPC_STUB(func_name, func_name, \
                MERCURY_GEN_TRUE, ret_type, -1, \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _in_t), HG_GEN_PARAM_NAME_SEQ(in_param_, in_types), \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _out_t), HG_GEN_PARAM_NAME_SEQ(out_param_, out_types), \
                MERCURY_GEN_FALSE, )

#define MERCURY_POSIX_GEN_CALLBACK_STUB_NOINPUT_NORET(func_name) \
        MERCURY_HANDLER_GEN_CALLBACK_STUB(BOOST_PP_CAT(func_name, _cb), func_name, \
                MERCURY_GEN_FALSE, , \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, )

#define MERCURY_POSIX_GEN_RPC_STUB_NOINPUT_NORET(func_name) \
        MERCURY_GEN_RPC_STUB(func_name, func_name, \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, )

#define MERCURY_POSIX_GEN_CALLBACK_BULK_STUB(func_name, ret_type, \
        in_types, out_types, bulk_read) \
        MERCURY_HANDLER_GEN_CALLBACK_STUB(BOOST_PP_CAT(func_name, _cb), func_name, \
                MERCURY_GEN_TRUE, ret_type, \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _in_t), HG_GEN_PARAM_NAME_SEQ(in_param_, in_types), \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _out_t), HG_GEN_PARAM_NAME_SEQ(out_param_, out_types), \
                MERCURY_GEN_TRUE, bulk_read)

#define MERCURY_POSIX_GEN_RPC_BULK_STUB(func_name, ret_type, \
        in_types, out_types, bulk_read) \
        MERCURY_GEN_RPC_STUB(func_name, func_name, \
                MERCURY_GEN_TRUE, ret_type, -1, \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _in_t), HG_GEN_PARAM_NAME_SEQ(in_param_, in_types), \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _out_t), HG_GEN_PARAM_NAME_SEQ(out_param_, out_types), \
                MERCURY_GEN_TRUE, bulk_read)

/* Set MERCURY_POSIX_SERVER before including the header to define server stubs */
#ifdef MERCURY_POSIX_SERVER
  #define MERCURY_POSIX_GEN_STUB_CLASS MERCURY_POSIX_GEN_CALLBACK_STUB
  #define MERCURY_POSIX_GEN_STUB_NOINPUT_NORET_CLASS MERCURY_POSIX_GEN_CALLBACK_STUB_NOINPUT_NORET
  #define MERCURY_POSIX_GEN_BULK_STUB_CLASS MERCURY_POSIX_GEN_CALLBACK_BULK_STUB
#else
  #define MERCURY_POSIX_GEN_STUB_CLASS MERCURY_POSIX_GEN_RPC_STUB
  #define MERCURY_POSIX_GEN_STUB_NOINPUT_NORET_CLASS MERCURY_POSIX_GEN_RPC_STUB_NOINPUT_NORET
  #define MERCURY_POSIX_GEN_BULK_STUB_CLASS  MERCURY_POSIX_GEN_RPC_BULK_STUB
#endif

#define MERCURY_POSIX_GEN_STUB(func_name, ret_type, in_types, out_types) \
        \
        /* Generate serialization / deserialization structs */ \
        MERCURY_GEN_PROC(BOOST_PP_CAT(func_name, _in_t), \
                HG_GEN_PARAM_NAME_SEQ(in_param_, in_types)) \
        MERCURY_GEN_PROC(BOOST_PP_CAT(func_name, _out_t), \
                HG_GEN_PARAM_NAME_SEQ(out_param_, out_types) \
                HG_GEN_RET_PARAM(ret_type)) \
        \
        /* Generate stub */ \
        MERCURY_POSIX_GEN_STUB_CLASS(func_name, ret_type, in_types, out_types)

#define MERCURY_POSIX_GEN_STUB_NOINPUT_NORET(func_name) \
        \
        /* Generate stub */ \
        MERCURY_POSIX_GEN_STUB_NOINPUT_NORET_CLASS(func_name)

#define MERCURY_POSIX_GEN_BULK_STUB(func_name, ret_type, in_types, out_types, bulk_read) \
        \
        /* Generate serialization / deserialization structs */ \
        MERCURY_GEN_PROC(BOOST_PP_CAT(func_name, _in_t), \
                HG_GEN_PARAM_NAME_SEQ(in_param_, in_types) \
                HG_BULK_PARAM) \
        MERCURY_GEN_PROC(BOOST_PP_CAT(func_name, _out_t), \
                HG_GEN_PARAM_NAME_SEQ(out_param_, out_types) \
                HG_GEN_RET_PARAM(ret_type)) \
        \
        /* Generate stub */ \
        MERCURY_POSIX_GEN_BULK_STUB_CLASS(func_name, ret_type, in_types, out_types, bulk_read)

/*****************************************************************************
 * High-level BOOST macros for server stub registration
 *****************************************************************************/
/* Register func_name */
#define MERCURY_POSIX_HANDLER_REGISTER(func_name) \
        MERCURY_HANDLER_REGISTER(BOOST_PP_STRINGIZE(func_name), \
                BOOST_PP_CAT(func_name, _cb), \
                BOOST_PP_CAT(func_name, _in_t), BOOST_PP_CAT(func_name, _out_t))

/*****************************************************************************
 * Backup (do not remove)
 *****************************************************************************/
#define MERCURY_GEN_CLIENT_STUB_FINALIZE() \
void hg_finalize_server(void) \
{ \
    int hg_ret, na_ret; \
    hg_bool_t hg_initialized, func_registered; \
    na_class_t *network_class; \
    char *server_name; \
    hg_request_t request; \
    na_addr_t addr; \
    hg_id_t id; \
    \
    HG_Initialized(&hg_initialized, &network_class); \
    if (!hg_initialized) { \
        HG_ERROR_DEFAULT("Mercury is not initialized"); \
        return; \
    } \
    \
    /* Get server_name if set */ \
    server_name = getenv(HG_PORT_NAME); \
    /* Look up addr id */ \
    na_ret = NA_Addr_lookup(network_class, server_name, &addr); \
    if (na_ret != NA_SUCCESS) { \
        HG_ERROR_DEFAULT("Could not lookup addr"); \
        return; \
    } \
    \
    /* Check whether call has already been registered or not */ \
    HG_Registered("MERCURY_REGISTER_FINALIZE", &func_registered, &id); \
    if (!func_registered) { \
        id = MERCURY_REGISTER_FINALIZE(); \
    } \
    \
    /* Forward call to remote addr and get a new request */ \
    hg_ret = HG_Forward(addr, id, NULL, NULL, &request); \
    if (hg_ret != HG_SUCCESS) { \
        HG_ERROR_DEFAULT("Could not forward call"); \
        return; \
    } \
    hg_ret = HG_Wait(request, HG_MAX_IDLE_TIME, HG_STATUS_IGNORE); \
    if (hg_ret != HG_SUCCESS) { \
        HG_ERROR_DEFAULT("Error during wait"); \
        return; \
    } \
}

#endif /* MERCURY_POSIX_MACROS_H */
