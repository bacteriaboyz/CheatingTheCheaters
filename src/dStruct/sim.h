#ifndef _SIM_H
#define _SIM_H

#include "types.h"
#include "graph.h"
#include "rng.h"
#include "nn.h"
#include "param.h"

typedef struct
{
    nnTree tree;        // Nearest Neighbor data structure
    rngState state;     // Random number generator stuff

    graphBac graph;     // Graph object with all bacteria and stuff
    paramSim param;     // Parameter struct with... parameters...

    cInt t;             // Current time variable in h, not time step constant!
    cFloat c_b;         // Concentration of antibiotic in blood at current time
    cInt dose_num;       // Tracks what dose number we are in treatment

} simBac;

#endif

