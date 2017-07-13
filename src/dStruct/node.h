#ifndef _NODE_H
#define _NODE_H

#include "types.h"
#include "hash.h"
#include "table.h"

struct nodeBac
{
    tableHash neighbors;    // Hash table with neighboring nodeBac structs
    cInt numNei;            // Number of neighbors

    cVec pos;               // Vector with position coordinates (x,y,z)

    cFloat alp_e;           // Effective replication rate, 1/h
    
    cFloat gam_e;           // Effective death rate, 1/h

    cFloat s_h;             // Plasmid uptake rate, 1/h

    cFloat ome_e;           // Event occurrence rate, 1/h
    
    cInt enz : 1;           // 2-bit allocation (assigns 1 bit to this variable,
                                // more efficient than booleans).

    cInt used : 1;          // Used to avoid setting nulls
};

typedef struct nodeBac nodeBac;
#endif
