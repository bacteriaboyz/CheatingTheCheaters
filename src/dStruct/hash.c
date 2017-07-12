#include "hash.h"

#define HASH_BIG_INIT (0x6c62272e07bb0142 * 0x8000000000000000 * 0x2 + \
    0x62b821756295c58d)

#define HASH_BIG_PRIME_INIT (0x8000000000000000 * 0x2000000 + 0x100 + 0x3b)

#define HASH_SMALL_INIT (0x1000000 + 0x100 + 0x93)

#define HASH_SMALL_PRIME_INIT 0x1000193

cBigInt hash128(char *key, cInt len)
{
    cBigInt hash = HASH_BIG_INIT;
    cBigInt prime = HASH_BIG_PRIME_INIT;

    for (cInt i = 0; i < len; ++i)
    {
        hash = (hash ^ key[i]) * prime;
    }

    return hash;
}

uint32_t hash32(char *key, cInt len)
{
    uint32_t hash = HASH_SMALL_INIT;
    uint32_t prime = HASH_SMALL_PRIME_INIT;

    for (cInt i = 0; i < len; ++i)
    {
        hash = (hash ^ key[i]) * prime;
    }

    return hash;
}
