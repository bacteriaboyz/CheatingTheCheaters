#ifndef _NODE_H
#define _NODE_H

#include "types.h"

struct nodeBac
{
    struct nodeBac **neighbors;
    cFloat *distances;
    cInt len;

    cFloat x, y, z;

    cFloat enzyme;
    cFloat ab_init;
    cFloat ab_eff;

    cInt resistant : 1;
    cInt used : 1;
};

typedef struct nodeBac nodeBac;
#endif
