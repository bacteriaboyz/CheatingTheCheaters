#include "updatePARep.h"

#include "abLocal.h"
#include "map.h"


/* 
 * Function used by hash table iterator to check if neighbor is a producer.
 * If so, then the neighbor's corresponding distance is saved.
 * 
 * Arguments:   node the neighbor we're looking at right now
 *              dist that neighbor's associated distance in the hash table
 *              store_dist poiinter to the float array used to store all 
 *                  distances of producer neighbors
 * 
 * Returns:     void
 * 
 * Errors:      ?
 */

void updatePARep(nodeBac *node, simBac *sim)
{
    cFloat total_effort = 1.0 + node->num_r_n; 
        // will contain effort of all neighbors plus self
    nodeBac *n; // will handle output of iterator function
    cFloat d; // will handle output of iterator function

    cInt i=0; // counts through resistant neighbors 
    mapMagical(&n,&d,node->neighbors); // initialize map iterator
    while (i<node->num_r_n) // while not all resistant neighbors have been found
    {
        mapMagical(&n,&d,node->neighbors); // get next neighbor and distance
        if (n->enz && n->used) // if the neighbor is a producer and is alive
        { 
            total_effort -= ( sim->c_b - abConc(d,sim) ) / \
                ( sim->c_b - sim->param.c_c ); 
                // subtract effort saved by each neighbor
            ++i; // advance resistant neighbor counter
        }
    }

    node->p_a_r = sim->param.t_s * sim->param.alp_n * \ 
            // base probability
        ( 1.0 - ( node->numNei / sim->param.n_n_max ) ) * \
            // population density penalty
        total_effort / ( node->num_r_n + 1.0 ) * \
            // Effort distribution among producer neighbors
        sim->param.f_e; // producer penalty

}