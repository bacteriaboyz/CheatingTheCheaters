#include <math.h>
#include <string.h>

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

static void nnBucketCoords(
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

void nnInit(nnBuckets *nn, cVec sides, cInt *counts, errorCode *error)
{
    mapInitBucketTable(&nn->bucketTable, 1, error);

    if (*error == MEM)
    {
        return;
    }

    memcpy(nn->sides, sides, sizeof(nn->sides));
    memcpy(nn->counts, counts, sizeof(nn->counts));
}


void nnAdd(nnBuckets *nn, nodeBac *bacterium, errorCode *error)
{
    cInt coords[LIMITS_DIM];
    bucketBac bucket, *bucket_ptr;

    nnBucketCoords(nn, bacterium, coords, error);

    if (*error == INCONSISTENT)
    {
        return;
    }

    cInt idx = nnCoords2Idx(coords);

    bucket_ptr = mapLookupBucket(&nn->bucketTable, idx);

    if (bucket_ptr)
    {
        setAdd(&bucket, bacterium, error);
    }
    else
    {
        setInit(&bucket, 1, error);

        if (*error == MEM)
        {
            return;
        }

        setAdd(&bucket, bacterium, error);

        mapAddBucket(&nn->bucketTable, idx, &bucket, error);

        if (*error == MEM)
        {
            setFree(&bucket);
        }
    }
}

void nnDel(nnBuckets *nn, nodeBac *bacterium, errorCode *error)
{
    cInt coords[LIMITS_DIM];
    bucketBac *bucket_ptr;

    nnBucketCoords(nn, bacterium, coords, error);

    if (*error == INCONSISTENT)
    {
        return;
    }

    cInt idx = nnCoords2Idx(coords);

    bucket_ptr = mapLookupBucket(&nn->bucketTable, idx);

    if (!bucket_ptr)
    {
        *error = INCONSISTENT;
        return;
    }

    setDel(bucket_ptr, bacterium, error);

    switch (*error)
    {
        case NOT_FOUND:
            *error = INCONSISTENT; // We want it to fall through here.
        case MEM:
            return;
    }

    if (setIsEmpty(bucket_ptr))
    {
        setFree(bucket_ptr);

        mapDelBucket(&nn->bucketTable, idx, error);
    }
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
        *out = mapLookupBucket(&nn->bucketTable, nnCoords2Idx(new_coords));

        return;
    }

    *error = SUCCESS;
    *out = NULL;
}

void nnFree(nnBuckets *nn)
{
    for (cInt i = 0; i < nn->bucketTable.len; ++i)
    {
        if (nn->bucketTable.slots[i].used)
        {
            setFree((bucketBac *)&nn->bucketTable.slots[i].val);
        }
    }

    tableFree(&nn->bucketTable);
}
