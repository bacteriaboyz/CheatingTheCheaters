#ifndef _RNG_H
#define _RNG_H

#include <stdint.h>

#include "types.h"

typedef uint64_t rngState[2];

/*
 * Uses the FNV-1a 128 bit hash to initialize the state of the RNG. After
 * initialization, the generator is "spun" through several blocks to get rid of
 * any artifacts from bad seeds.
 */

void rngInitState(rngState state, char *phrase);

/*
 * Outputs a pseudorandom 64-bit block and updates the state.
 * Uses xorshift128+.
 */

uint64_t rngNextBlock(rngState state);

#endif
