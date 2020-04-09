/// @file utils_prng.h
/// @brief the interface for adapting PRNG functions.
///
///

#ifndef _UTILS_PRNG_H_
#define _UTILS_PRNG_H_

#include <stdint.h>


typedef struct {
    uint8_t Key[32];
    uint8_t V[16];
} prng_t;


int prng_set(prng_t *ctx, const void *prng_seed, unsigned long prng_seedlen);

int prng_gen(prng_t *ctx, unsigned char *out, unsigned long outlen);





#endif // _UTILS_PRNG_H_


