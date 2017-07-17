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
    char vtk_file_name[80];
    snprintf(vtk_file_name, 80, "pos_%s_%d.vtk", sim->name_run, sim->t);
    vtk_f = fopen(vtk_file_name, "w");
    
    if(!vtk_f)
    {
        *err = ERROR_CREATE_FILE;
        fclose(vtk_f);
        return;
    }
    
    FILE *vtk_f2;
    char vtk_file_name2[80];
    snprint(vtk_file_name2, 80, "col_%s_%d.vtk", sim->name_run, sim->t);
    vtk_f2 = fopen(vtk_file_name2, "w");
   
    if(!vtk_f2)
    {
        *err = ERROR_CREATE_FILE;
        fclose(vtk_f2);
        fclose(vtk_f);
        return;
    }
   
    chk = fprint(vtk_f, "# vtk DataFile Version 2.0\n \
    %s \nASCII \nDATASET POLYDATA \nPOINTS %d float \n", vtk_file_name, sim->num_bac);
    if(chk < 0)
    {
        *err = PRINT_FAIL;
        fclose(vtk_f);
        fclose(vtk_f2);
        return;
    }
    chk = fprint(vtk_f2, "POINT_DATA %d \n SCALARS scalars float 1\n \
    LOOKUP_TABLE_colors \n", sim->num_bac);
    if(chk < 0)
    {
        *err = PRINT_FAIL;
        fclose(vtk_f);
        fclose(vtk_f2);
        return;
    }
    
    for (cInt i = 0; i < sim->num_bac; ++i)
    {
        chk = fprint(vtk_f2, "%d.0\n", i);
        if(chk < 0)
        {
            *err = PRINT_FAIL;
            fclose(vtk_f);
            fclose(vtk_f2);
            return;
        }
    }
    chk = fprint(vtk_f2, "LOOKUP_TABLE_colors %d\n", sim->num_bac);
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
        
        chk = fprintf(vtk_f, "%.6e %.6e %.6e\n", \
            sim->graph.bacteria[i].pos[0],sim->graph.bacteria[i].pos[1], \
            sim->graph.bacteria[i].pos[2]);
              
        if(chk < 0)
        {
            *err = PRINT_FAIL;
            fclose(vtk_f);
            fclose(vtk_f2);
            return;
        }
        
        chk = fprintf(vtk_f2, "%d 0 %d 1\n", r, b);
        if(chk < 0)
        {
            *err = PRINT_FAIL;
            fclose(vtk_f);
            fclose(vtk_f2);
            return;
        }
    }
    
    fclose(vtk_f);
    fclose(vtk_f2);
}