// Copyright (c) NetFoundry Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <mbedtls/pk.h>


#ifdef _WIN32
#pragma pack(push, cryptoki, 1)
#define CK_PTR *
#define CK_DECLARE_FUNCTION(returnType, name)  returnType __declspec(dllimport) name
#define CK_DECLARE_FUNCTION_POINTER(returnType, name) returnType __declspec(dllimport) (* name)
#define CK_CALLBACK_FUNCTION(returnType, name) returnType (* name)
#else
#define CK_PTR *
#define CK_DECLARE_FUNCTION(returnType, name)  returnType name
#define CK_DECLARE_FUNCTION_POINTER(returnType, name) returnType (* name)
#define CK_CALLBACK_FUNCTION(returnType, name) returnType (* name)
#endif

#ifndef NULL_PTR
#define NULL_PTR 0
#endif

#include "pkcs11/pkcs11.h"

#ifdef _WIN32
#pragma pack(pop, cryptoki)
#endif

#ifndef ZITI_SDK_MBED_P11_H
#define ZITI_SDK_MBED_P11_H

#ifndef MBEDTLS_PRIVATE
#define MBEDTLS_PRIVATE(x) x
#endif

#ifndef MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED
#define MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED MBEDTLS_ERR_PK_HW_ACCEL_FAILED
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct mp11_context_s {
    void *lib;
    CK_FUNCTION_LIST *funcs;
    CK_SESSION_HANDLE session;
    CK_LONG slot_id;
};

struct mp11_key_ctx_s {
    CK_OBJECT_HANDLE priv_handle;
    CK_OBJECT_HANDLE pub_handle;
    CK_MECHANISM_TYPE sign_mechanism;

    struct mp11_context_s *ctx;
    void *pub; // mbedtls_rsa_context or mbedtls_ecdsa_context
};

typedef struct mp11_context_s mp11_context;
typedef struct mp11_key_ctx_s mp11_key_ctx;

int mp11_load_key(mbedtls_pk_context *key, const char *path, const char *pin, const char *slot, const char *key_id);

int p11_load_ecdsa(mbedtls_pk_context *pk, struct mp11_key_ctx_s *pCtx, mp11_context *pS);

int p11_load_rsa(mbedtls_pk_context *pk, struct mp11_key_ctx_s *pCtx, mp11_context *pS);


const char *p11_strerror(CK_RV rv);

#ifdef __cplusplus
}
#endif

#endif //ZITI_SDK_MBED_P11_H
