#include <string.h>

#include "rng.h"
#include "hash.h"

void rngInitState(rngState state, cByte *phrase)
{
    if (!state || !phrase)
    {
        return;
    }

    cBigInt hash = hash128(phrase, strlen(phrase));

    state[0] = hash & 0xffffffffffffffff;
    state[1] = hash >> 64;

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
