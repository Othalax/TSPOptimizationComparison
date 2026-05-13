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
	std::vector<Individual> newPopulation = population;
	Individual bestInd = population[0];
	for (int i = 0; i < numEliteSites; ++i)
	{
		newPopulation[i] = searchNeighborhood(population[i], eliteSearchSize);
		if (newPopulation[i].getFitness() < bestInd.getFitness())
		{
			bestInd = newPopulation[i];
		}
	}

	for (int i = numEliteSites; i < numEliteSites + numSelectedSites; ++i)
	{
		newPopulation[i] = searchNeighborhood(population[i], selectedSearchSize);
		if (newPopulation[i].getFitness() < bestInd.getFitness())
		{
			bestInd = newPopulation[i];
		}
	}

	for (int i = numEliteSites + numSelectedSites; i < popSize; ++i)
	{
		newPopulation[i].randomize();
		if (newPopulation[i].getFitness() < bestInd.getFitness())
		{
			bestInd = newPopulation[i];
		}
	}

	population = std::move(newPopulation);
	std::vector<Individual> nextGen;

	nextGen.push_back(bestInd);

	while (nextGen.size() < popSize) {
		Individual& p1 = population[tournament()];
		Individual& p2 = population[tournament()];

		std::uniform_real_distribution<double> dist(0.0, 1.0);
		if (dist(rng) < crossProb)
		{
			std::pair<Individual, Individual> children = p1.crossover(p2, rng);
			children.first.evaluate(evaluator);
			nextGen.push_back(children.first);
			if (nextGen.size() < popSize)
			{
				children.second.evaluate(evaluator);
				nextGen.push_back(children.second);
			}
		}
		else
		{
			nextGen.push_back(p1);
		}
	}

	for (Individual& ind : nextGen) {
		std::uniform_real_distribution<double> dist(0.0, 1.0);
		if (dist(rng) < mutProb)
		{
			ind.mutate(rng);
			ind.evaluate(evaluator);
		}
	}

	population = std::move(nextGen);

	std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
		return a.getFitness() < b.getFitness();
		});

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
