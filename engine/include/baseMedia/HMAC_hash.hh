#ifndef _HMAC_HASH_HH
#define _HMAC_HASH_HH

#ifndef _NET_COMMON_H
#include "NetCommon.h"
#endif

// All HMAC hash functions have the following signature:
typedef void HMAC_hash(u_int8_t const* key, unsigned keyLength, u_int8_t const* text, unsigned textLength, u_int8_t* resultDigest);
    // "resultDigest" must point to an array of sufficient size to hold the digest

#define HMAC_BLOCK_SIZE 64

#endif
