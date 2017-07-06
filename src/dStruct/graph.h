#ifndef _GRAPH_H
#define _GRAPH_H

#include "limits.h"
#include "node.h"
#include "types.h"

typedef struct
{
    nodeBac bacteria[LIMITS_MAX_BACT];
    cInt stack[LIMITS_MAX_BACT + 1];

    cInt idx;
} graphBac;

#endif
