#include "GeneticAlgorithm.h"
#include "ProblemLoader.h"
#include "BeesAlgorithm.h"

int main()
{
	std::string filepath = "data/eil51.tsp";
	ProblemLoader problem_loader(filepath);
	ProblemData problem_data = problem_loader.loadProblem();
	Evaluator evaluator(problem_data, problem_data.getDimension());

	/*int popSize = 100;
	double crossProb = 0.9;
	double mutProb = 0.35;
	int iterations = 1000;
	GeneticAlgorithm ga(popSize, crossProb, mutProb, evaluator);
	ga.initialize(iterations);
	const std::vector<int>* best_solution = ga.getBest();
	double best_fitness = ga.getBestFitness();
	std::cout << "final best fitness: " << best_fitness << std::endl;
	std::cout << "best solution: ";
	for (int gene : *best_solution) {
		std::cout << gene << " ";
	}*/

	int popSize = 100;
	int numEliteSites = 5;
	int eliteSearchSize = 20;
	int numSelectedSites = 20;
	int selectedSearchSize = 10;
	int iterations = 1000;
	BeesAlgorithm ba(popSize, numEliteSites, eliteSearchSize, numSelectedSites, selectedSearchSize, evaluator);
	ba.initialize(iterations);
	const std::vector<int>* best_solution = ba.getBest();
	double best_fitness = ba.getBestFitness();
	std::cout << "final best fitness: " << best_fitness << std::endl;
	std::cout << "best solution: ";
	for (int gene : *best_solution) {
		std::cout << gene << " ";
	}

}