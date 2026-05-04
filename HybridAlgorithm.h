#pragma once

#include "Individual.h"


class HybridAlgorithm
{
public:
    HybridAlgorithm(int popSize, double crossProb, double mutProb, 
                    int numEliteSites, int eliteSearchSize, int numSelectedSites,
                    int selectedSearchSize, Evaluator& evaluator);

    void initialize(int iterations);
    const std::vector<int>* getBest();
    double getBestFitness() const;

private:
    void runIteration();
    int tournament();
    Individual searchNeighborhood(const Individual& ind, int searchSize);

    int popSize;
    double crossProb, mutProb;
    int numEliteSites, eliteSearchSize;
    int numSelectedSites, selectedSearchSize;
    Evaluator& evaluator;

    std::vector<Individual> population;

    std::mt19937 rng;
};

