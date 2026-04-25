#include "BeesAlgorithm.h"

BeesAlgorithm::BeesAlgorithm(int popSize, int numEliteSites, int eliteSearchSize, int numSelectedSites,
    int selectedSearchSize, Evaluator& evaluator) 
	: popSize(popSize), numEliteSites(numEliteSites), eliteSearchSize(eliteSearchSize), 
	numSelectedSites(numSelectedSites), selectedSearchSize(selectedSearchSize), 
	evaluator(evaluator)
{
}

void BeesAlgorithm::initialize(int iterations)
{
	
}

std::vector<int>* BeesAlgorithm::getBest()
{
	return population[0].getGenotype();
}

double BeesAlgorithm::getBestFitness() const
{
	return population[0].getFitness();
}

void BeesAlgorithm::runIteration()
{
}

void BeesAlgorithm::neighborhoodSearch()
{
}



