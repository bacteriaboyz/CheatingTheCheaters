#include "hash.h"

#define HASH_INIT (0x6c62272e07bb0142 * 0x8000000000000000 * 0x2 + \
    0x62b821756295c58d)

#define HASH_PRIME_INIT (0x8000000000000000 * 0x2000000 + 0x100 + 0x3b)

cBigInt hash128(char *key, cInt len)
{
    cBigInt hash = HASH_INIT;
    cBigInt prime = HASH_PRIME_INIT;

    for (cInt i = 0; i < len; ++i)
    {
        hash = (hash ^ key[i]) * prime;
    }

    return hash;
}
