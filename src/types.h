#ifndef _TYPES_H
#define _TYPES_H

#include <inttypes.h>

#include "limits.h"

#define TYPES_CBYTE(x) ((cByte *)(x))

#define TYPES_READ SCNuFAST32
#define TYPES_WRITE PRIuFAST32

typedef char cByte;
typedef uint_fast32_t cInt;

#ifdef OLD_GCC
typedef __uint128_t cBigInt;
#else
typedef unsigned __int128 cBigInt;
#endif

typedef double cFloat;
typedef cFloat cVec[LIMITS_DIM];

#endif
