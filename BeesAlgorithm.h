#pragma once

#include "Individual.h"

class BeesAlgorithm
{
public:
    BeesAlgorithm(int popSize, int numEliteSites, int eliteSearchSize, int numSelectedSites, 
                  int selectedSearchSize, Evaluator& evaluator);

    void initialize(int iterations);
    const std::vector<int>* getBest();
    double getBestFitness() const;

private:
    void runIteration();
	Individual searchNeighborhood(const Individual& ind, int searchSize);

    int popSize;
    int numEliteSites, eliteSearchSize;
    int numSelectedSites, selectedSearchSize;
    Evaluator& evaluator;

    std::vector<Individual> population;

    std::mt19937 rng;
};

