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
	for (int i = 0; i < popSize; i++)
	{
		Individual ind(evaluator.getSolutionSize());
		ind.randomize();
		ind.evaluate(evaluator);
		population.push_back(ind);
	}

	std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
		return a.getFitness() < b.getFitness();
		});

	for (int i = 0; i < iterations; i++)
	{
		runIteration();
	}
}

const std::vector<int>* HybridAlgorithm::getBest()
{
	return population[0].getGenotype();
}

double HybridAlgorithm::getBestFitness() const
{
	return population[0].getFitness();
}

void HybridAlgorithm::runIteration()
{
	std::vector<Individual> newPopulation;
	newPopulation.push_back(population[0]);


}

int HybridAlgorithm::tournament()
{
	std::uniform_int_distribution<int> dist(0, (int)population.size() - 1);
	int b1 = dist(rng), b2 = dist(rng);
	return (population[b1].getFitness() < population[b2].getFitness()) ? b1 : b2;
}

Individual HybridAlgorithm::searchNeighborhood(const Individual& ind, int searchSize)
{
	Individual best = ind;

	for (int i = 0; i < searchSize; ++i)
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
