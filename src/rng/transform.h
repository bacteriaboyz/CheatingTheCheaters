#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "errors.h"
#include "types.h"

/*
 * Returns a cFloat uniformly distributed between "l" and "u".
 */

cFloat transformUnif(rngState state, cFloat l, cFloat u);

/*
 * Returns a standard normal variate.
 */

cFloat transformGauss(rngState state, errorCode *error);

/*
 * Given a radius and a center, samples a point uniformly from the ball and
 * writes it to "out".
 */

void transformBall(
                    rngState state,
                    cFloat radius,
                    cVec center,
                    cVec out,
                    errorCode *error
                  );

#endif
