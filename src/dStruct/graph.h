#ifndef _GRAPH_H
#define _GRAPH_H

#include "limits.h"
#include "node.h"
#include "types.h"
#include "stack.h"
#include "set.h"

typedef struct
{
    nodeBac bacteria[LIMITS_MAX_BACT];  // Contains all bacteria in simulation,
                                            // in use and out of use
    
    stackBac rep_stack;                 // Stack of pointers to bacteria to be 
                                            // replicated this time step
    stackBac die_stack;                 // Stack of pointers to bacteria to be 
                                            // killed this time step
    stackBac hgt_stack;                 // Stack of pointers to bacteria to be 
                                            // transferred plasmids this tstep
    setBac update_set;                  // Set of nodes to be updated this t_s
    
    stackBac dead_stack;                // Stack of pointers to bacteria not 
                                            // currently in use.
} graphBac;

#endif
