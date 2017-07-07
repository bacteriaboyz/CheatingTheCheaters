#include <string.h>

#include "rng.h"

#define RNG_MASK 0x00000000ffffffff

/*
 * Performs multiplication of 128-bit values "a" and "b" represented in base
 * 2^32 with 4 64-bit digits (32 bits for value plus 32 bits for holding
 * carries). Only the bottom 128 bits of the multiplication are retained. The
 * result is written back into "a".
 */

static void rngMul128(uint64_t *a, uint64_t *b)
{
    uint64_t c[4];

    // Compute word 0 and carry once.
    c[0] = a[0] * b[0];
    c[1] = c[0] >> 32;
    c[0] &= RNG_MASK;

    // Compute word 1 and carry twice.
    c[1] += a[0] * b[1];
    c[2] = c[1] >> 32;
    c[1] &= RNG_MASK;

    c[1] += a[1] * b[0];
    c[2] += c[1] >> 32;
    c[1] &= RNG_MASK;

    // Compute word 2 and carry thrice.
    c[2] += a[0] * b[2];
    c[3] = c[2] >> 32;
    c[2] &= RNG_MASK;

    c[2] += a[1] * b[1];
    c[3] += c[2] >> 32;
    c[2] &= RNG_MASK;

    c[2] += a[2] * b[0];
    c[3] += c[2] >> 32;
    c[2] &= RNG_MASK;

    // Compute word 3 without carries.
    c[3] += a[0] * b[3] + a[1] * b[2] + a[2] * b[1] + a[3] * b[0];
    c[3] &= RNG_MASK;

    memcpy(a, c, 32);
}

void rngInitState(rngState state, char *phrase)
{
    if (!state || !phrase)
    {
        return;
    }

    uint64_t hash[] = { 0x6295c58d, 0x62b82175, 0x07bb0142, 0x6c62272e };
    uint64_t fnv_prime[] = { 0x0000013b, 0, 0x01000000, 0 };

    for (; *phrase; ++phrase)
    {
        hash[0] ^= *phrase;

        rngMul128(hash, fnv_prime);
    }

    state[0] = hash[1] << 32 | hash[0];
    state[1] = hash[3] << 32 | hash[2];

    for (cInt i = 0; i < 128; ++i)
    {
        rngNextBlock(state);
    }
}

uint64_t rngNextBlock(rngState state)
{
    uint64_t x = state[0];
    uint64_t y = state[1];

    state[0] = y;

    x ^= (x << 23);

    return (state[1] = x ^ y ^ (x >> 18) ^ (y >> 5)) + y;
}
