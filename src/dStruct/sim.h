#ifndef _SIM_H
#define _SIM_H

#include "graph.h"
#include "rng.h"
#include "types.h"

typedef struct
{
    graphBac *graph;

    nnTree *tree;

    rngState state;

    cInt t_step;
} simBac;

#endif
