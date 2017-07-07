void reproductionBac(*nodeBac node, *graphBac graph, simBac sim, rngState rand_State)
{
    //TODO: assign new node location using random sampling thing
    //      define child_X, child_Y, child_Z
    //TODO: assign new node neighbors and distances using nn tree thing 
    //      define neigh and dist arrays, num_neigh int

   nodeBac child = 
    {
        neighbors=neigh,
        distances=dist,
        len=num_neigh,
        deg=num_neigh,
        x=child_X,y=child_Y,z=child_Z,
        fitness=0,
        resistant=node.resistant, // by default, same as parent
        used=1
    };

    if (transform.rand(rand_State) < sim.p_RN*node.resistant + sim.p_NR*(!node.resistant)) 
        // Calculate conditional probability of child bacteria mutating
    {
        child.resistant = !child.resistant; // mutate from parent
    }

    fitnessUpdate(child);    

    if (node.resistant) // only update fitness statuses if new child is resistant
    {
        for (cInt i=0; i < node.len; i++)
        {
            fitnessUpdate(node->neighbors[i]);
        }
    }

    return;
}
