#include "GeneticAlgorithm.h"
#include "ProblemLoader.h"

int main()
{
	std::string filepath = "data/eil51.tsp";
	ProblemLoader problem_loader(filepath);
	ProblemData problem_data = problem_loader.loadProblem();
	Evaluator evaluator(problem_data, problem_data.getDimension());

	int popSize = 100;
	double crossProb = 0.5;
	double mutProb = 0.6;
	int iterations = 1000;
	GeneticAlgorithm ga(popSize, crossProb, mutProb, evaluator);
	ga.initialize(iterations);
	std::vector<int>* best_solution = ga.getBest();
	double best_fitness = ga.getBestFitness();
	std::cout << "final best fitness: " << best_fitness << std::endl;
	std::cout << "best solution: ";
	for (int gene : *best_solution) {
		std::cout << gene << " ";
	}


}