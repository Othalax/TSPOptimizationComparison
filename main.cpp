#include "GeneticAlgorithm.h"
#include "ProblemLoader.h"
#include "BeesAlgorithm.h"
#include "HybridAlgorithm.h"

int main()
{
	std::string filepath = "data/eil51.tsp";
	ProblemLoader problem_loader(filepath);
	ProblemData problem_data = problem_loader.loadProblem();
	Evaluator evaluator(problem_data, problem_data.getDimension());
	int seed = std::random_device{}();

	//int popSize = 100;
	double crossProb = 0.5;
	double mutProb = 0.05;
	//int iterations = 1000;
	/*GeneticAlgorithm ga(popSize, crossProb, mutProb, evaluator, seed);
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
	int eliteSearchSize = 30;
	int numSelectedSites = 30;
	int selectedSearchSize = 10;
	int iterations = 1000;
	BeesAlgorithm ba(popSize, numEliteSites, eliteSearchSize, numSelectedSites, selectedSearchSize, evaluator, seed);
	ba.initialize(iterations);
	double best_fitnessb = ba.getBestFitness();
	std::cout << "final best fitness: " << best_fitnessb << std::endl;

	HybridAlgorithm ha(popSize, crossProb, mutProb, numEliteSites, eliteSearchSize, numSelectedSites, selectedSearchSize, evaluator, seed);
	ha.initialize(iterations);
	double best_fitness = ha.getBestFitness();
	std::cout << "final best fitness: " << best_fitness << std::endl;
	std::cout << std::endl;

}