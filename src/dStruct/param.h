#ifndef _PARAM_H
#define _PARAM_H

#include "types.h"

typedef struct
{
    // Physical and Biological parameters:
    
    cFloat z_max;       // Biofilm thickness, max value, um
    cFloat d_bac;       // Distance between centers of two bacteria, um
    cFloat gam_n;       // Death rate in the absence of antibiotic, 1/h
    cFloat lam_l;       // Plasmid loss rate at replication, 1/(cell*h)
    cFloat lam_t;       // Plasmid transfer rate, um^3/(cell*h)
    cFloat bet_c;       // Fraction of total bath concentration of substance
                            //  assumed as cutoff point for radius of influence
                            // (i.e. neighborhood size), dimensionless
    cFloat r_c;         // Bacteria cell radius, um
    cFloat alp_n;       // Replication rate of non-producer bacteria in absence
                            // of antibiotic
    cFloat x_max;       // Simulation plane length, um
    cFloat x_base_factor;   // Number of times the sim base is length is larger
                                // than the sow base length
    cFloat t_s;         // Simulation time step, h
    cFloat t_max;       // Max simulation time, h
    cFloat v_w;         // German automobile manufacturer, horsepower
                            //  ...
                            // ...fine, total body water, L
    cFloat t_b;         // Total body mass, kg

    // Control parameters:

    cFloat k_a;         // Clearance rate of antibiotic from blood plasma, L/h
    cFloat c_i;         // Concentration of antibiotic at 50\% growth 
                            // inhibition (IC_50), um/mL
    cFloat h_i;         // Initial height of bacterial biofilm, fraction of 
                            // total simulation thickness
    cFloat phi_i;       // Initial proportion of resistant bacteria in biofilm,
                            // dimensionless
    cFloat c_m;         // Minimum Inhibitory Concentration (MIC) of antibiotic,
                            // um/mL
    cFloat c_c;         // Concentration of antibiotic at cell wall of 
                            // resistant bacteria, um/mL
    cFloat f_e;         // Relative fitness of enzyme producers to 
                            // non--producers in absence of antibiotic
    cInt num_doses;     // Number of doses being administered
    cFloat *doses_t;    // Pointer to an array with times at which 
                            // antibiotic is administered, h
    cFloat *doses_c;    // Pointer to an array with concentrations in blood 
                            // after administering each each dose, ug/mL
    
    // Simulation parameters:

    cFloat snap_freq;   // Snapshot frequency, h
    char name_run[LIMITS_MAX_LINE_LEN];     // Stores name of this run
    bool output;        // True if you want frame by frame output
    
    // Parameters calculated during initialization:
    cFloat rho_b;       // Max biofilm density, cells/um^3
    cFloat r_d;         // Radius of diffusion cutoff, um
    cFloat v_n;         // Volume of neighborhood sphere, um^3
    cFloat v_t;         // Volume of total simulation
    cFloat n_n_max;     // Maximum number of bacteria in neighborhood
    cFloat n_max;       // Maximum number of bacteria in simulation
    cFloat gam_ab;      // Concentration decay rate of antibiotic in blood, 
                            // mL^-1
    cFloat c_h;         // Concentration of antibiotic that causes probability
                            // of dying at replication to be 50%
    cFloat h;           // Hill coefficient for antibiotic's Hill dose impact 
                            // equation

} paramSim;

#endif
