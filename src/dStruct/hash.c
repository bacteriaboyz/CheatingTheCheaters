#include "hash.h"

#define HASH_INIT (0x6c62272e07bb0142 * 0x8000000000000000 * 0x2 + \
    0x62b821756295c58d)

#define HASH_PRIME_INIT (0x8000000000000000 * 0x2000000 + 0x100 + 0x3b)

cBigInt hash128(char *key)
{
    cBigInt hash = HASH_INIT;
    cBigInt prime = HASH_PRIME_INIT;

    for (char *ptr = key; *ptr; ++ptr)
    {
        hash = (hash ^ *ptr) * prime;
    }

    return hash;
}
