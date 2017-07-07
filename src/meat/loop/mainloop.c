cFloat mainloopCall(*graphBac graph, *simBac sim, rng randState)
{
    for (cInt i=0; i< sim->num_Iter; i++)
    {
        if (transformUnif(randState,0.0,1.0) < graphBac->bacteria[i].fitness)
        {
            reproductionBac(graph->bacteria[i], graph, randState);
                // replicate this node if the probability is below this 
                // bacteria's fitness 
        }
        if (transformUnif(randState,0.0,1.0) < sim->p_Death)
        {
            deathBac(i,graph);
                // kill this bacteria depending on a constant probability
        }

        if (i % sim->snap_freq == 0)
        {
            //TODO: write snapshot of graph struct  to file
        }
    }
     
    //TODO: write snapshot of graph struct  to file 
}
