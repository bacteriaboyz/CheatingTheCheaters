#ifndef _LIMITS_H
#define _LIMITS_H

#ifndef M_PI
#define M_PI 3.14159265358979323846 // Fuck C99 in particular
#endif

#ifndef LIMITS_MAX_TRIES
#define LIMITS_MAX_TRIES 128
#endif

#ifndef LIMITS_MAX_BACT
#define LIMITS_MAX_BACT 10000
#endif

#ifndef LIMITS_DIM
#define LIMITS_DIM 3
#endif

#if LIMITS_DIM != 3
#error "Simulations other than 3D are left as an exercise for the reader ;)"
#endif

// How wide each coordinate is in the bucket index.
#define LIMITS_BCOORD_WIDTH (32 / LIMITS_DIM)

#if LIMITS_DIM == 1
#define LIMITS_BCOORD_MAX 0xffffffff
#else
#define LIMITS_BCOORD_MAX ((1 << LIMITS_BCOORD_WIDTH) - 1)
#endif

#ifndef LIMITS_BNEIGHBORS
#define LIMITS_BNEIGHBORS 27 // 3 ^ LIMITS_DIM
#endif

#ifndef LIMITS_TABLE_ENTRY_SIZE
#define LIMITS_TABLE_ENTRY_SIZE 64 // size of Intel cache line
#endif

#ifndef LIMITS_MAX_LINE_LEN
#define LIMITS_MAX_LINE_LEN 80
#endif

#ifndef LIMITS_MAX_FILE_SIZE
#define LIMITS_MAX_FILE_SIZE (1024 * 1024)
#endif

#endif
