#include "pHGT.h"

void updatePHGT(nodeBac *node, simBac *sim)
{
    if (node->enz)
    {
         node->p_hgt = 0;
            // if this bacteria is a producer, it doesn't matter if it gets 
                // another plasmid
    }
    else
    {
        node->p_hgt = sim->param.t_s * sim->param.lam_t * node->num_r_n / \
            sim->param.v_n;
            // depends on population density of neighborhood
    }
}

