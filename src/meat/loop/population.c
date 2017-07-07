cFloat populationEff(nodeBac *node, simBac *sim)
{
    return 1-1/(1+(1/(1-simBac->rep_0)-1)*exp(-1*simBac->max_Growth)); 
    // 1 - logistic equation. x_0 is 1 - initial replication rate
}
