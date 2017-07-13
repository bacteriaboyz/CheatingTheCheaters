#include "dieRate.h"

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

#include <math.h>

void updatePDie(nodeBac *node, simBac *sim);
{
    node->p_die = ( simBac->param.gam_n * simBac->param.t_s + \
        ( 1.0 - simBac->param.gam_n * simBac->param.t_s) ) * \
        nodeBac->p_a_r * nodeBac->p_a_d * ( 1.0 - nodeBac->p_hgt );
}
