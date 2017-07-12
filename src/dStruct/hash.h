#ifndef _HASH_H
#define _HASH_H

#include "types.h"

/*
 * Uses the FNV-1a 128-bit hash algorithm.
 */

cBigInt hash128(char *key);

#endif
