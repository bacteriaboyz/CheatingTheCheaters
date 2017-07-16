#include <stdio.h>
#include <math.h>

#include "init.h"

void initSim(simBac *sim, char *param_file, errorCode *err)
{
    // Get parameters:
    //FILE *file;
    //file = fopen("test.txt", "r");
    // TODO: read param_file

    // Calculate remaining parameters:
    sim->param.v_t = pow( sim->param.x_max, 2.0 ) * sim->param.z_max;
    sim->param.n_max = sim->param.v_t / \
        ( 4.0 * sqrt(2.0) * pow( sim->param.d_bac, 3.0 ) );
        // 3D sphere packing formula for bacterial density
    sim->param.rho_b = sim->param.n_n_max / sim->param.v_t;
    sim->param.r_d = sim->param.r_c / ( 1.0 - sim->param.bet_c );
        // see document for derivation
    sim->param.v_n = 4.0 * M_PI * pow( sim->param.r_d, 3.0 ) / 3.0;
    sim->param.n_n_max = sim->param.rho_b * sim->param.v_n;
    sim->param.gam_ab = sim->param.t_s * sim->param.k_a / sim->param.v_w;
        // renal clearance in time step
    sim->param.c_h = ( sim->param.c_i + sim->param.c_m ) / 2.0;
        // midpoint, hill function is symmetrical around midoint
    sim->param.h = log( 2.0 ) / \
        ( log( 1.0 + ( sim->param.c_m / sim->param.c_i ) ) - log( 2.0 ) );
        // Hill coefficient expressed in terms of 1/3 and 2/3 total height pts.
    
    // Sow initial cells
    
}
