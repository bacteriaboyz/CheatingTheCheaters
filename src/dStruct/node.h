#ifndef _NODE_H
#define _NODE_H

#include "types.h"
#include "hash.h"
#include "table.h"
#include "errors.h"
#include "limits.h"

typedef struct
{
    tableHash neighbors;    // Hash table with neighboring nodeBac structs
    cInt num_r_n;           // Number of resistance enzyme-producing neighbors

    cVec pos;               // Vector with position coordinates (x,y,z)
    cInt enz : 1;           // Producer of enzyme, 1 or 0
                                // 2-bit allocation (assigns 1 bit to this
                                // more efficient than booleans).

    cFloat dProd;           // Distance to the nearest enzyme producer
    cFloat c;               // Concentration of antibiotic felt at this node
    cFloat v_n;             // Volume of neighborhood around bacteria
    cFloat p_a_r;           // Probability of attempting replication in t step
    cFloat p_a_d;           // Probability of death at replication due to AB
    cFloat p_rep;           // Effective replication probability in time step
    cFloat p_die;           // Effective death probability in time step
    cFloat p_hgt;           // Plasmid uptake probability in time step

    cInt used : 1;          // Used to avoid setting nulls
} nodeBac;

#endif
