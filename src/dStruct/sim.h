#ifndef _SIM_H
#define _SIM_H

#include "types.h"
#include "graph.h"
#include "rng.h"
#include "nn.h"
#include "param.h"

typedef struct
{
    graphBac graph;     // Graph object with all bacteria and stuff

    nnTree tree;        // Nearest Neighbor data structure

    rngState state;     // Random number generator stuff

    cInt t;             // Current time variable in h, not time step constant!

    cFloat c_b;         // Concentration of antibiotic in blood at current time

    cInt dose_num;       // Tracks what dose number we are in treatment

    paramSim param;     // Parameter struct with... parameters...

} simBac;

#endif

