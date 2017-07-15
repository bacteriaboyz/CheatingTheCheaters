#include <math.h>
#include "neighVol.h"

void updateNeiVol(nodeBac *node, simBac *sim)
{
    node->v_n = sim->param.v_n; // volume of this neighborhood
    cFloat dif[2]; // contain overflow distances
    dif[0] = node->pos[LIMITS_DIM-1] + sim->param.r_d - sim->param.z_max;
        // overflow at top
    dif[1] = sim->param.r_d - node->pos[LIMITS_DIM-1];
        // overflow at bottom
    for (cInt i=0; i<2; i++) // repeat for every side
    {
        if (dif[i] > 0) // if sphere is cut at bottom,
        {
            node->v_n -= M_PI * pow( dif[i], 2.0) * \
                ( 3.0 * sim->param.r_d - dif[i] ) / 3.0;
                // formula for sphere cap
        }
    }
}
