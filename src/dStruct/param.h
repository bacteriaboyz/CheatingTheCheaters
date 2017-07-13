#ifndef _PARAM_H
#define _PARAM_H

#include "types.h"

typedef struct
{
    // Physical and Biological parameters:
    
    cFloat rho_b;       // Max biofilm density, cells/um^3
    cInt z_max;         // Biofilm thickness, um
    cFloat gam_n;       // Death rate in the absence of antibiotic, 1/h
    cFloat lam_l;       // Plasmid loss rate at replication, 1/(cell*h)
    cFloat lam_t        // Plasmid transfer rate, um^3/(cell*h)
    cFloat bet_c        // Fraction of total bath concentration of substance
                            //  assumed as cutoff point for radius of influence
                            // (i.e. neighborhood size), dimensionless
    cFloat r_c;         // Bacteria cell radius, um
    cFloat alp_n;       // Replication rate of non-producer bacteria in absence
                            // of antibiotic
    cFloat x_max;       // Simulation plane length, um
    cFloat t_s;         // Simulation time step, h
    cFloat t_max;       // Max simulation time, h
    cFloat v_w;         // German automobile manufacturer, horsepower
                            //  ...
                            // ...fine, total body water, L

    // Control parameters:

    cFloat k_a;         // Clearance rate of antibiotic from blood plasma, L/h
    cFloat c_i;         // Concentration of antibiotic at 50\% growth 
                            // inhibition (IC_50), um/mL
    cFloat rho_i;       // Initial population density of bacteria in biofilm,
                            // cells/um^3
    cFloat phi_i;       // Initial proportion of resistant bacteria in biofilm,
                            // dimensionless
    cFloat c_m;         // Minimum Inhibitory Concentration (MIC) of antibiotic,
                            // um/mL
    cFloat c_c;         // Concentration of antibiotic at cell wall of 
                            // resistant bacteria, um/mL
    cFloat f_e;         // Relative fitness of enzyme producers to 
                            // non--producers in absence of antibiotic
    cInt doses_t[];     // Times at which antibiotic is administered, h
    cFloat doses_c[];   // Concentrations in blood after administering each 
                            // each dose, ug/mL
    
    // Simulation parameters:

    cInt snap_freq;     // Snapshot frequency (in time steps)

    // Parameters calculated during initialization:
    cFloat r_d;         // Radius of diffusion cutoff, um
    cFloat n_n_max;     // Maximum number of bacteria in neighborhood
    cFloat n_max;       // Maximum number of bacteria in simulation

} paramSim;

#endif

