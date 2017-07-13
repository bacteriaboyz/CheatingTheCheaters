#ifndef _HASH_H
#define _HASH_H

#include <stdint.h>

#include "types.h"

/*
 * Uses the FNV-1a 128-bit hash algorithm.
 */

cBigInt hash128(cByte *key, cInt len);

/*
 * Uses the FNV-1a 32-bit hash algorithm.
 */

cInt hash32(cByte *key, cInt len);

#endif
