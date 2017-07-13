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

    // Biological parameters:
    cFloat p_Death; // probability of bacteria dying in the time step
    
    //Simulation parameters:
    cInt snap_freq; // snapshot frequency (in time steps)

} simBac;

#endif

