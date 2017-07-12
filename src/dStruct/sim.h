#ifndef _SIM_H
#define _SIM_H

#include "types.h"
#include "graph.h"
#include "rng.h"
#include "nn.h"

typedef struct
{
    graphBac graph;

    nnTree tree;

    rngState state;

    cInt t_step;
} simBac;

#endif
