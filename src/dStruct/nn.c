#include <stdlib.h>
#include <math.h>

#include "limits.h"
#include "map.h"
#include "nn.h"

static cInt nnCoords2Idx(cInt *coords)
{
    cInt idx = 0;

    for (cInt i = 0; i < LIMITS_DIM; ++i)
    {
        idx = idx << LIMITS_BCOORD_WIDTH | coords[i];
    }

    return idx;
}

void nnBucketCoords(
                    nnBuckets *nn,
                    nodeBac *bacterium,
                    cInt *coords,
                    errorCode *error
                   )
{
    for (cInt i = 0; i < LIMITS_DIM; ++i)
    {
        cFloat coord = floor(bacterium->pos[i] / nn->sides[i]);

        if (coord > LIMITS_BCOORD_MAX)
        {
            *error = INCONSISTENT;
        }

        coords[i] = (cInt)coord;
    }

    *error = SUCCESS;
}

void nnIterator(
                nnBuckets *nn,
                setBac **out,
                nodeBac *bacterium,
                errorCode *error
               )
{
    static cInt coords[LIMITS_DIM];
    static cInt offset;

    if (bacterium)
    {
        nnBucketCoords(nn, bacterium, coords, error);
        offset = 0;
        return;
    }

    for (; offset < LIMITS_BNEIGHBORS; ++offset)
    {
        cInt decode = offset;
        cInt new_coords[LIMITS_DIM];

        for (cInt i = 0; i < LIMITS_DIM; ++i)
        {
            switch (decode % 3)
            {
                case 0:
                    new_coords[i] = coords[i];
                    break;
                case 1:
                    new_coords[i] = (coords[i] + 1) % nn->counts[i];
                    break;
                case 2:
                    new_coords[i] = coords[i] == 0 ?
                                        nn->counts[i] - 1 :
                                        coords[i] - 1;
                    break;
            }

            decode /= 3;
        }

        *error = SUCCESS;
        *out = mapLookupBucket(nn->bucketTable, nnCoords2Idx(new_coords));

        return;
    }

    *error = SUCCESS;
    *out = NULL;
}
