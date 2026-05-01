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
	population.clear();
	for (int i = 0; i < popSize; ++i) 
	{
		Individual ind(evaluator.getSolutionSize());
		ind.randomize();
		population.push_back(ind);
	}
	for (int i =0; i < iterations; ++i) 
	{
		runIteration();
	}
	
}

const std::vector<int>* BeesAlgorithm::getBest()
{
	return population[0].getGenotype();
}

double BeesAlgorithm::getBestFitness() const
{
	return population[0].getFitness();
}

void BeesAlgorithm::runIteration()
{
	std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
		return a.getFitness() < b.getFitness();
		});

	std::vector<Individual> newPopulation = population;
	for (int i = 0; i < numEliteSites; ++i) 
	{
		newPopulation[i] = searchNeighborhood(population[i], eliteSearchSize);
	}

	for (int i = numEliteSites; i < numEliteSites + numSelectedSites; ++i) 
	{
		newPopulation[i] = searchNeighborhood(population[i], selectedSearchSize);
	}

	for (int i = numEliteSites + numSelectedSites; i < popSize; ++i) 
	{
		newPopulation[i].randomize();
	}

	population = std::move(newPopulation);
}

Individual BeesAlgorithm::searchNeighborhood(const Individual& ind, int searchSize)
{
	Individual best = ind;

	for (int k = 0; k < searchSize; ++k)
	{
		Individual candidate = ind;
		candidate.neighborhoodSearch(evaluator, rng);

		if (candidate.getFitness() < best.getFitness())
		{
			best = candidate;
		}
	}

	return best;
}



