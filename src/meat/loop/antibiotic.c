cFloat antibioticEff(nodeBac *node, simBac *sim)
{
    enz = enzymeConc(node, sim); // get enzyme concentration at this point

    //TODO: code for concentration of AB given enzyme concentration

    return 1-1/(1+(1/(1-simBac->rep_0)-1)*exp(-1*simBac->min_Inhib_Conc//TODO figure out influence using minimum inhibitory concentration)); 
    // 1 - logistic equation. x_0 is 1 - initial replication rate
}
