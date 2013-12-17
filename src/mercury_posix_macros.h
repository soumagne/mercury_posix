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
        MERCURY_HANDLER_GEN_CALLBACK_STUB(BOOST_PP_CAT(func_name, _cb), BOOST_PP_CAT(hg_posix_, func_name), \
                MERCURY_GEN_TRUE, ret_type, \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _in_t), HG_GEN_PARAM_NAME_SEQ(in_param_, in_types), \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _out_t), HG_GEN_PARAM_NAME_SEQ(out_param_, out_types), \
                MERCURY_GEN_FALSE, )

#define MERCURY_POSIX_GEN_RPC_STUB(func_name, ret_type, in_types, out_types) \
        MERCURY_GEN_RPC_STUB(BOOST_PP_CAT(hg_posix_, func_name), BOOST_PP_CAT(hg_posix_, func_name), \
                MERCURY_GEN_TRUE, ret_type, 0, \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _in_t), HG_GEN_PARAM_NAME_SEQ(in_param_, in_types), \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _out_t), HG_GEN_PARAM_NAME_SEQ(out_param_, out_types), \
                MERCURY_GEN_FALSE, )

#define MERCURY_POSIX_GEN_CALLBACK_STUB_NOINPUT_NORET(func_name) \
        MERCURY_HANDLER_GEN_CALLBACK_STUB(BOOST_PP_CAT(func_name, _cb), BOOST_PP_CAT(hg_posix_, func_name), \
                MERCURY_GEN_FALSE, , \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, )

#define MERCURY_POSIX_GEN_RPC_STUB_NOINPUT_NORET(func_name) \
        MERCURY_GEN_RPC_STUB(BOOST_PP_CAT(hg_posix_, func_name), BOOST_PP_CAT(hg_posix_, func_name), \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, , , \
                MERCURY_GEN_FALSE, )

#define MERCURY_POSIX_GEN_CALLBACK_BULK_STUB(func_name, ret_type, \
        in_types, out_types, bulk_read) \
        MERCURY_HANDLER_GEN_CALLBACK_STUB(BOOST_PP_CAT(func_name, _cb), BOOST_PP_CAT(hg_posix_, func_name), \
                MERCURY_GEN_TRUE, ret_type, \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _in_t), HG_GEN_PARAM_NAME_SEQ(in_param_, in_types), \
                MERCURY_GEN_TRUE, BOOST_PP_CAT(func_name, _out_t), HG_GEN_PARAM_NAME_SEQ(out_param_, out_types), \
                MERCURY_GEN_TRUE, bulk_read)

#define MERCURY_POSIX_GEN_RPC_BULK_STUB(func_name, ret_type, \
        in_types, out_types, bulk_read) \
        MERCURY_GEN_RPC_STUB(BOOST_PP_CAT(hg_posix_, func_name), BOOST_PP_CAT(hg_posix_, func_name), \
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
        MERCURY_HANDLER_REGISTER(BOOST_PP_STRINGIZE(BOOST_PP_CAT(hg_posix_, func_name)), \
                BOOST_PP_CAT(func_name, _cb), \
                BOOST_PP_CAT(func_name, _in_t), BOOST_PP_CAT(func_name, _out_t))

#endif /* MERCURY_POSIX_MACROS_H */
