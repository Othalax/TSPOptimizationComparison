#pragma once

#include "Evaluator.h"
#include <random>
#include <set>

class Individual {
public:
    Individual();
    Individual(int size);
	Individual(std::vector<int> route);
    Individual(const Individual& other);

    Individual& operator=(const Individual& other);


    double evaluate(Evaluator& evaluator);
    void mutate(double mutProb, std::mt19937& rng);
	void randomize();
    Individual crossover(const Individual& other, std::mt19937& rng) const;

    double getFitness() const;
    std::vector<int>* getGenotype();

private:

    std::vector<int> route;
    double fitness;
};

