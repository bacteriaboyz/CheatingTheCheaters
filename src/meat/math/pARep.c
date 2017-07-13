#include "updatePARep.h"

#include "sim.h"
#include "types.h"
#include "graph.h"
#include "limits.h"
#include "node.h"
#include "hash.h"
#include "table.h"
#include "bucket.h"
#include "errors.h"
#include "stack.h"
#include "rng.h"
#include "nn.h"
#include "param.h"

#include "abLocal.h"

#include <math.h>

void updatePARep(nodeBac *node, simBac *sim);
{
    cFloat total_effort = 1.0 + nodeBac->num_r_n; // will contain all neighbor 
                                                        // and self efforts
    cFloat distances[nodeBac->num_r_n]; // will contain distances to resistant 
                                            // neighbors

    //TODO: use iterator to get all resistant neighbor distances passing &distances and checking for no errors

    for (cInt i=0; i<nodeBac->num_r_n; i++) // iterate through all neighbors
    {
        total_effort -= ( sim->c_b - abConc(distances[i]) ) / \
            ( sim->c_b - sim->param.c_c ); // subtract effort saved by each
                                                // neighbor
    }

    node->p_rep = simBac->param.t_s * simBac->param.alp_n * \ 
            // base probability
        ( 1.0 - ( nodeBac->numNei / simBac->param.n_n_max ) ) * \
            // population density penalty
        ( total_effort )  / ( nodeBac->num_r_n + 1.0 ) * \
            // Effort distribution among producer neighbors
        simBac->param.f_e; // producer penalty

}
