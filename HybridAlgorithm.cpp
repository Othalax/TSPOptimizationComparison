#include "HybridAlgorithm.h"

HybridAlgorithm::HybridAlgorithm(int popSize, double crossProb, double mutProb, 
								 int numEliteSites, int eliteSearchSize, int numSelectedSites,
								 int selectedSearchSize, Evaluator& evaluator)
	: popSize(popSize), crossProb(crossProb), mutProb(mutProb),
	  numEliteSites(numEliteSites), eliteSearchSize(eliteSearchSize),
	  numSelectedSites(numSelectedSites), selectedSearchSize(selectedSearchSize),
	  evaluator(evaluator), rng(std::random_device{}())
{
}

void HybridAlgorithm::initialize(int iterations)
{
}

const std::vector<int>* HybridAlgorithm::getBest()
{
	return nullptr;
}

double HybridAlgorithm::getBestFitness() const
{
	return 0.0;
}

void HybridAlgorithm::runIteration()
{
}

int HybridAlgorithm::tournament()
{
	return 0;
}

Individual HybridAlgorithm::searchNeighborhood(const Individual& ind, int searchSize)
{
	return ind;
}
