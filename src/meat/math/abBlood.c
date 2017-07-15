#include "abBlood.h"

void updateAB(simBac *sim)
{
    sim->c_b = ( 1.0 - sim->param.gam_ab ) * sim->c_b * ( sim->param.t_s );
        // Exponential decay according to renal clearance rate

    if (sim->t >= sim->param.doses_t[sim->dose_num]) 
        // If we're at the next dosing time...
    {
        sim->c_b += sim->param.doses_c[sim->dose_num]; 
            // Add concentration of next dose to blood       
        ++sim->dose_num; // Advance dose counter
    }
}
