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
    void mutate(std::mt19937& rng);
	void randomize();
	std::pair<Individual, Individual> crossover(const Individual& other, std::mt19937& rng) const;
    //Individual crossover(const Individual& other, std::mt19937& rng) const;
	void neighborhoodSearch(Evaluator& evaluator);

    double getFitness() const;
    std::vector<int>* getGenotype();

private:

    std::vector<int> route;
    double fitness;
};

