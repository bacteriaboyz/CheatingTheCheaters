#ifndef _SIM_H
#define _SIM_H

#include <stdio.h>

#include "types.h"
#include "graph.h"
#include "rng.h"
#include "nn.h"
#include "param.h"

typedef struct
{
    // Structures
    nnBuckets buckets;  // Nearest Neighbor data structure
    graphBac graph;     // Graph object with all bacteria and stuff
    paramSim param;     // Parameter struct with... parameters...

    // Simulation state variables
    rngState state;     // Random number generator stuff
    cFloat t;           // Current time variable in h, not time step constant!
    cFloat t_last_snap; // Time elapsed since last snapshot
    cFloat c_b;         // Concentration of antibiotic in blood at current time
    cFloat c_b_peak;    // Keeps track of previous dosage peak concentration
                            // for exponential decay function
    cInt dose_num;      // Tracks what dose number we are in treatment
    cInt num_bac;       // Number of bacteria at this moment
    cInt num_pro;       // Number of producer bacteria at this moment

    FILE *t_series_file;// Stores pointer to time series file

} simBac;

#endif
