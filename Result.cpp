#include "Result.h"

Result::Result(Evaluator& evaluator, int GApopsize, double GAcrossprob, double GAmutprob, int GAinterations, int BApopSize, int BAnumEliteSites, 
				int BAeliteSearchSize, int BAnumSelectedSites, int BAselectedSearchSize, int BAinterations, int HApopsize, 
				double HAcrossprob, double HAmutprob, int HAnumEliteSites, int HAeliteSearchSize, int HAnumSelectedSites, 
				int HAselectedSearchSize, int HAiterations)
	: evaluator(evaluator), GApopsize(GApopsize), GAcrossprob(GAcrossprob), GAmutprob(GAmutprob), GAinterations(GAinterations), BApopSize(BApopSize),
	  BAnumEliteSites(BAnumEliteSites), BAeliteSearchSize(BAeliteSearchSize), BAnumSelectedSites(BAnumSelectedSites),
	  BAselectedSearchSize(BAselectedSearchSize), BAinterations(BAinterations), HApopsize(HApopsize), HAcrossprob(HAcrossprob),
	  HAmutprob(HAmutprob), HAnumEliteSites(HAnumEliteSites), HAeliteSearchSize(HAeliteSearchSize), HAnumSelectedSites(HAnumSelectedSites),
	  HAselectedSearchSize(HAselectedSearchSize), HAiterations(HAiterations)
{
}

void Result::runAlgorithms(int seednum)
{
	double avgtimeGA = 0;
	double avgtimeBA = 0;
	double avgtimeHA = 0;

	double avgfitnessGA = 0.0;
	double avgfitnessBA = 0.0;
	double avgfitnessHA = 0.0;

	for (int i = 1; i <= seednum; i++)
	{
		GeneticAlgorithm ga(GApopsize, GAcrossprob, GAmutprob, evaluator, i);
		auto startTime = std::chrono::high_resolution_clock::now();

		ga.initialize(GAinterations);

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = endTime - startTime;
		avgtimeGA += elapsed.count();
		avgfitnessGA += ga.getBestFitness();
	}

	avgtimeGA /= seednum;
	avgfitnessGA /= seednum;

	std::cout << "Genetic Algorithm\n" << "Time: " << avgtimeGA << "  Fitness: " << avgfitnessGA << "\n\n";

	for (int i = 1; i <= seednum; i++)
	{
		BeesAlgorithm ba(BApopSize, BAnumEliteSites, BAeliteSearchSize, BAnumSelectedSites, BAselectedSearchSize, evaluator, seednum);
		auto startTime = std::chrono::high_resolution_clock::now();

		ba.initialize(BAinterations);

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = endTime - startTime;
		avgtimeBA += elapsed.count();
		avgfitnessBA += ba.getBestFitness();
	}

	avgtimeBA /= seednum;
	avgfitnessBA /= seednum;

	std::cout << "Bees Algorithm\n" << "Time: " << avgtimeBA << "  Fitness: " << avgfitnessBA << "\n\n";

	for (int i = 1; i <= seednum; i++)
	{
		HybridAlgorithm ha(HApopsize, HAcrossprob, HAmutprob, HAnumEliteSites, HAeliteSearchSize, HAnumSelectedSites, HAselectedSearchSize, evaluator, seednum);
		auto startTime = std::chrono::high_resolution_clock::now();

		ha.initialize(HAiterations);

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = endTime - startTime;
		avgtimeHA += elapsed.count();
		avgfitnessHA += ha.getBestFitness();
	}

	avgtimeHA /= seednum;
	avgfitnessHA /= seednum;

	std::cout << "Hybrid Algorithm\n" << "Time: " << avgtimeHA << "  Fitness: " << avgfitnessHA << "\n\n";
}
