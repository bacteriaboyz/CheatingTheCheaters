#include <stdlib.h>
#include "pARep.h"

void updatePARep(nodeBac *node, simBac *sim)
{
    cFloat total_effort = 0; 
        // will contain effort of all neighbors plus self
    nodeBac *n; // will handle output of iterator function
    cFloat d; // will handle output of iterator function

    cInt i=0; // counts through resistant neighbors 
    mapState state;
    mapInitMagic(&state, &node->neighbors); // initialize map iterator
    if (node->enz) // if producer of enzyme
    {
        while (i<node->num_r_n) // while not all resistant neighbors have been found
        {
            mapMagical(&state, &n, &d); // get next neighbor and distance
            
            if (n->enz && n->used)
                 // if the neighbor OR SELF is a producer and is alive
            { 
                total_effort += ( abConc(d,sim) - sim->param.c_c ) /\
                    ( sim->c_b - sim->param.c_c ); 
                    // subtract effort saved by each neighbor
                ++i; // advance resistant neighbor counter
            }
        }
    }

    node->p_a_r = sim->param.t_s * sim->param.alp_n * \
            // base probability
        ( 1.0 - ( tableCard(&node->neighbors) / \
            // tableCard returns number of neighbors
        ( node->v_n * sim->param.rho_b ) ) ) * \
            // last two lines: population density penalty
        ( 1.0 - ( total_effort / ( node->num_r_n + 1.0 ) ) * \
            // Effort distribution among producer neighbors
        ( 1.0 - sim->param.f_e ) ); // producer penalty
    
    if (node->p_a_r < 0) 
        // Due to stochastic effects, logistic term may in fact return negative
        // so we have to account for that
    {
        node->p_a_r = 0;
    }
}
