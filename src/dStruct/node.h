#ifndef _NODE_H
#define _NODE_H

#include "types.h"
#include "hash.h"
#include "table.h"

typedef struct
{
    tableHash neighbors;    // Hash table with neighboring nodeBac structs
    cInt num_nei;           // Number of neighbors
    cInt num_r_n;           // Number of resistance enzyme-producing neighbors

    cVec pos;               // Vector with position coordinates (x,y,z)
    cFloat p_a_r;           // Probability of attempting replication in t step
    cFloat p_a_d;           // Probability of death at replication due to AB
    cFloat p_rep;           // Effective replication probability in time step
    cFloat p_die;           // Effective death probability in time step
    cFloat p_hgt;           // Plasmid uptake probability in time step
    cFloat p_evt;           // Event occurrence probability in time step

    cInt enz : 1;           // Producer of enzyme, true/false variable
                                // 2-bit allocation (assigns 1 bit to this
                                // more efficient than booleans).
    cInt used : 1;          // Used to avoid setting nulls
} nodeBac;

#endif
