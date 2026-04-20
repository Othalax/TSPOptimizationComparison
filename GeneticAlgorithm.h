#pragma once

#include "Individual.h"


class GeneticAlgorithm {
public:
    GeneticAlgorithm(int popSize, double crossProb, double mutProb, Evaluator& evaluator);

    void initialize(int iterations);
    std::vector<int>* getBest();
    double getBestFitness() const;

private:
    void runIteration();
    int tournament();

    int popSize;
    double crossProb, mutProb;
    Evaluator& evaluator;

    std::vector<Individual> population;
    Individual bestIndividual;

    std::mt19937 rng;
};
