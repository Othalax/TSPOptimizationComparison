#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, Evaluator& evaluator)
	: popSize(popSize), crossProb(crossProb), mutProb(mutProb), 
	evaluator(evaluator), iterationsWithoutImprovement(0) 
{
}

void GeneticAlgorithm::initialize(int iterations)
{
	for(int i = 0; i < popSize; ++i) 
	{
		Individual ind(evaluator.getSolutionSize());
		ind.randomize();
		population.push_back(ind);
	}
	bestIndividual = population[0];
	bestIndividual.evaluate(evaluator);
	for (int i = 0; i < popSize; ++i) 
	{
		if (population[i].evaluate(evaluator) < bestIndividual.getFitness()) 
		{
			bestIndividual = population[i];
		}
	}

	for(int i = 0; i < iterations; ++i) 
	{
		runIteration();
	}
}

std::vector<int>* GeneticAlgorithm::getBest()
{
	return bestIndividual.getGenotype();
}

double GeneticAlgorithm::getBestFitness() const
{
	return bestIndividual.getFitness();
}

void GeneticAlgorithm::runIteration()
{
}

int GeneticAlgorithm::tournament()
{
	return 0;
}

void GeneticAlgorithm::diversifyPopulation()
{
}
