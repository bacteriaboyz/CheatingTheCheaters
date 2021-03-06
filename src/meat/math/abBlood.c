#include <math.h>
#include "abBlood.h"

void updateAB(simBac *sim)
{
    cFloat prev_t = 0; // time of last spike
    if (sim->dose_num > 0) // if we've already started administering drugs,
    {
        prev_t = sim->param.doses_t[sim->dose_num-1]; // set time of last spike to that
    }
    sim->c_b = sim->c_b_peak * \
        exp( -1 * sim->param.k_a * \
        ( sim->t - prev_t ) \
        / sim->param.v_w );
        // Exponential decay from last time spike
        // ( 1.0 - sim->param.t_s * sim->param.gam_ab ) * sim->c_b;
        // Exponential decay according to renal clearance rate
    
    if (sim->dose_num < sim->param.num_doses) // if under total number of doses
    {
        if (sim->t >= sim->param.doses_t[sim->dose_num]) 
            // If we're at the next dosing time...
        {
            sim->c_b += sim->param.doses_c[sim->dose_num] * \
                sim->param.t_b / sim->param.v_w; 
                // Add concentration of next dose to blood, calculated
                    // from net dose, body mass and total body water
            ++sim->dose_num; // Advance dose counter
            sim->c_b_peak = sim->c_b; // set new peak concentration
        }
    }
}
