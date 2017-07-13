#include "antibiotic.h"

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

void updateAB(simBac *sim)
{
    sim->c_b = ( 1 - sim->param.k_a * sim->param.v_w ) * sim->c_b * \
        ( sim->t-sim -> param.t_s );
        // Exponential decay according to renal clearance rate

    if (sim->t == sim->param.doses_t[sim->dose_num]) // If we're at the next 
                                                        // dosing time...
    {
        sim->c_b += sim->param.doses_c[sim->dose_num]; // Add concentration of
                                                        // next dose to blood       
        ++sim->dose_num; // Advance dose counter
    }
}
