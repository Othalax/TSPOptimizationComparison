#pragma once

#include "Evaluator.h"
#include <random>

class Individual {
public:
    Individual();
    Individual(int size);
    Individual(const Individual& other);

    Individual& operator=(const Individual& other);


    double evaluate(Evaluator& evaluator);
    void mutate(double mutProb, std::mt19937& rng);
    std::pair<Individual*, Individual*> crossover(const Individual& other, std::mt19937& rng) const;

    double getFitness() const;
    void setFitness(double fit);
    std::vector<int>* getGenotype();

private:

    std::vector<int> route;
    double fitness;
};

