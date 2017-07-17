#include <studio.h>

#include "snapshot.h"

void snapshotSim(simBac *sim, errorCode *err)
{
    //For the csv file
    cInt chk = fprintf(sim->t_series_file, "%.6e,%d,%d,%.6e\n", sim->t, sim->num_bac, sim->num_pro, sim->c_b);
    cInt r;
    cInt b;
    
    if(chk < 0)
    {
        *err = PRINT_FAIL;
        return;
    }
    
    
    //for the VTK file
    
    FILE *vtk_f;
    char utk_file_name[80];
    snprintf(vtk_file, name, 80, "anim_%s_%d.vtk", sim->name_run, sim->t);
    
    vtk_f = fopen(vtk_file_name, "w");
    if(!vtk_f)
    {
        *err = ERROR_CREATE_FILE;
        fclose(vtk_f);
        return;
    }
    
    for (cInt i = 0; i < sim->num_bac; ++i)
    {   
        if(sim->graph.bacteria[i].enz == 1)
        {
            r = 1;
            b = 0;
        }
        else
        {
            r = 0;
            b = 1;
        }    
        chk = fprintf(vtk_f, "%.6e,%.6e,%.6e,%d,0,%d,1\n", \
            sim->graph.bacteria[i].pos[0],sim->graph.bacteria[i].pos[1], \
            sim->graph.bacteria[i].pos[2], r, 0, b, 1);
        
        if(chk < 0)
        {
            *err = PRINT_FAIL;
            fclose(vtk_f);
            return;
        }
    }
    
    fclose(vtk_f);
}