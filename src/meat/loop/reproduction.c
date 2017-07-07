#include <math.h>

#include "reproduction.h"
#include "transform.h"
#include "fitness.h"

void reproductionBac(nodeBac *node, graphBac *graph, simBac *sim)
{
    //TODO: assign new node location using random sampling thing
    //      define child_X, child_Y, child_Z
    //TODO: assign new node neighbors and distances using nn tree thing
    //      define neigh and dist arrays, num_neigh int

   nodeBac child =
    {
        .neighbors=neigh,
        .distances=dist,
        .len=num_neigh,
        .deg=num_neigh,
        .pos=position,
        .fitness=0,
        .resistant=node->resistant, // by default, same as parent
        .used=1
    };

    if (transformUnif(sim->state, 0.0, 1.0)) < sim.p_RN * node->resistant + sim.p_NR * (!node->resistant)) //TODO: split into ifs
        // Calculate conditional probability of child bacteria mutating
    {
        child.resistant = !child.resistant; // mutate from parent
    }

    fitnessUpdate(child);

    if (node->resistant) // only update fitness statuses if new child is resistant
    {
        for (cInt i=0; i < node->len; ++i)
        {
            fitnessUpdate(node->neighbors[i]);
        }
    }

    return;
}
