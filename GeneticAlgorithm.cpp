#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, Evaluator& evaluator)
	: popSize(popSize), crossProb(crossProb), mutProb(mutProb), 
	evaluator(evaluator), rng(std::random_device{}())
{
}

void GeneticAlgorithm::initialize(int iterations)
{
    population.clear();
	bestIndividual = Individual(evaluator.getSolutionSize());
	bestIndividual.randomize();
	bestIndividual.evaluate(evaluator);
    population.push_back(bestIndividual);
	
	for(int i = 1; i < popSize; ++i) 
	{
		Individual ind(evaluator.getSolutionSize());
		ind.randomize();
		population.push_back(ind);

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

const std::vector<int>* GeneticAlgorithm::getBest()
{
	return bestIndividual.getGenotype();
}

double GeneticAlgorithm::getBestFitness() const
{
	return bestIndividual.getFitness();
}

void GeneticAlgorithm::runIteration()
{
    std::vector<Individual> nextGen;

    nextGen.push_back(bestIndividual);

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
        if (ind.getFitness() < bestIndividual.getFitness()) {
            bestIndividual = ind;
        }
    }

    population = std::move(nextGen);
}

int GeneticAlgorithm::tournament()
{
    std::uniform_int_distribution<int> dist(0, (int)population.size() - 1);
    int b1 = dist(rng), b2 = dist(rng);
    return (population[b1].getFitness() < population[b2].getFitness()) ? b1 : b2;
}

