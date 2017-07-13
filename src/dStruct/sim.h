#ifndef _SIM_H
#define _SIM_H

#include "types.h"
#include "graph.h"
#include "rng.h"
#include "nn.h"
#include "parameter.h"

typedef struct
{
    graphBac graph;     // Graph object with all bacteria and stuff

    nnTree tree;        // Nearest Neighbor data structure

    rngState state;     // Random number generator stuff

    cInt t_step;        // Time step number, not constant!

    paramSim param;     // Parameter struct with... parameters...

} simBac;

#endif

