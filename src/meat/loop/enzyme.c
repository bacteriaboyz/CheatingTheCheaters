#include <math.h>

#include "enzyme.h"

cFloat enzymeConc(nodeBac *node, simBac *sim)
{
    cFloat enz = 0; // stores enzyme concentration added from all neighbors
    for (cInt i=0; i < node->len; i++)
    {
        if (node->neighbors[i].used && node->resistant)
        {
            enz += sim->ab_prod/(2*sqrt(sim->dif_Enz*sim->deg_Enz))*exp(-1*sqrt(sim->deg_Enz/sim->dif_Enz)*node->distances[i])
                // Solution of diffusion equation with constant degradation and point source, solved at equilibrium
        }
    }

    return enz;
}
