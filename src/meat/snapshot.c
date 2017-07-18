#include <stdio.h>
#include <math.h>

#include "snapshot.h"
#include "types.h"

void snapshotSim(simBac *sim, errorCode *err)
{
    //For the csv file
    cInt chk = fprintf(sim->t_series_file, "%.6e,%" TYPES_WRITE ",%" \
        TYPES_WRITE ",%.6e\n", sim->t, sim->num_bac, sim->num_pro, sim->c_b);

    if(chk < 0)
    {
        *err = PRINT_FAIL;
        return;
    }

    //for the VTK file
    FILE *vtk_f;
    char vtk_file_name[LIMITS_MAX_LINE_LEN];
    snprintf(vtk_file_name, LIMITS_MAX_LINE_LEN, "pos_%s_%.4f.vtk", \
        sim->param.name_run, floor(sim->t/sim->param.snap_freq));
    
    vtk_f = fopen(vtk_file_name, "w");

    if(!vtk_f)
    {
        *err = ERR_CREATE_FILE;
        return;
    }

    chk = fprintf(vtk_f, "# vtk DataFile Version 2.0\n"
        "%s \nASCII \nDATASET POLYDATA \nPOINTS %" TYPES_WRITE 
        " float \n", vtk_file_name, sim->num_bac);
    if(chk < 0)
    {
        *err = PRINT_FAIL;
        goto ss_jmp1;
    }
    
    for (cInt i = 0; i < LIMITS_MAX_BACT; ++i)
    {
        if (sim->graph.bacteria[i].used)
        {
            chk = fprintf(vtk_f, "%.6e %.6e %.6e\n", \
                sim->graph.bacteria[i].pos[0],sim->graph.bacteria[i].pos[1], \
                sim->graph.bacteria[i].pos[2]);

            if(chk < 0)
            {
                *err = PRINT_FAIL;
                goto ss_jmp1;
            }

            
        }
    }
    
    fprintf(vtk_f,"POINT_DATA %" TYPES_WRITE "\n SCALARS enzyme float\n" "LOOKUP_TABLE Producers\n", sim->num_bac);
    
    for (cInt i = 0; i < LIMITS_MAX_BACT; ++i)
    {
        if (sim->graph.bacteria[i].used)
        {        
            chk = fprintf(vtk_f, "%" TYPES_WRITE"\n", (cInt)sim->graph.bacteria[i].enz );
            if(chk < 0)
            {
                *err = PRINT_FAIL;
                goto ss_jmp1;
            }
        }
    }
    
    *err = SUCCESS;
    
ss_jmp1:
    fclose(vtk_f);
}
