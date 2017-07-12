#include <math.h>

#include "limits.h"
#include "rng.h"
#include "transform.h"

#define TRANSFORM_DENOMINATOR 0x20000000000000

cFloat transformUnif(rngState state, cFloat l, cFloat u)
{
    cFloat raw = (cFloat)(rngNextBlock(state) >> (64 - 53));

    return fma(u - l, raw / TRANSFORM_DENOMINATOR, l);
}

cFloat transformGauss(rngState state, errorCode *error)
{
    for (cInt i = 0; i < LIMITS_MAX_TRIES; ++i)
    {
        cFloat u = transformUnif(state, -1, 1);
        cFloat v = transformUnif(state, -1, 1);

        cFloat s = u * u + v * v;

        if (s > 0 && s < 1)
        {
            *error = SUCCESS;
            return u * sqrt(-2 * log(s) / s);
        }
    }

    *error = REJECT;
    return 0;
}

void transformBall(
                    rngState state,
                    cFloat radius,
                    cVec center,
                    cVec out,
                    errorCode *error
                  )
{
    cFloat coef = 0;
    cFloat new_radius = radius * pow(
        transformUnif(state, 0, 1),
        (cFloat)1 / LIMITS_DIM
    );

    for (cInt i = 0; i < LIMITS_DIM; ++i)
    {
        cFloat v = transformGauss(state, error)

        if (*error == REJECT)
        {
            return;
        }

        out[i] = v;

        coef += v * v;
    }

    coef = new_radius / sqrt(coef);

    for (cInt i = 0; i < LIMITS_DIM; ++i)
    {
        out[i] = fma(out[i], coef, center[i]);
    }

    *error = SUCCESS;
}
