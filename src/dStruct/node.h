#ifndef _NODE_H
#define _NODE_H

#include "types.h"

struct nodeBac
{
    struct nodeBac **neighbors;
    cFloat *distances;
    cInt len;
    cInt deg;           // Equal to number of used nodes in neighbors

    cVec pos;

    cFloat fitness;
    cInt resistant : 1; // 2-bit allocation (assigns 1 bit to this variable,
                        // more efficient than booleans).

    cInt used : 1;      // Used to avoid setting nulls
};

typedef struct nodeBac nodeBac;
#endif
