void fitnessUpdate(nodeBac *node, simBac *sim)
{
    cFloat eff_AB = antibioticEff(node,sim); // Masking effect of antibiotic
    cFloat eff_Pop = populationEff(node,sim); // Masking effect of population

    cFloat res_Mask = 1; // Resistance fitness penalty (default no penalty)
    if (node.resistant)
    {
        res_Mask = sim->res_Fitness; // Resistance fitness penalty
    }

    node->fitness = 1*res_Mask*eff_AB*eff_Pop; // calculates final fitness

    return;
}
