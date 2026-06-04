#include "ProblemLoader.h"
#include "Result.h"

int main()
{
	std::string filepath = "data/eil101.tsp";
	ProblemLoader problem_loader(filepath);
	ProblemData problem_data = problem_loader.loadProblem();
	Evaluator evaluator(problem_data, problem_data.getDimension());
	
	// Genetic algorithm parameters
	int GApopsize = 100;
	double GAcrossprob = 0.7;
	double GAmutprob = 0.2;
	int GAinterations = 1000;

	// Bees algorithm parameters
	int BApopSize = 100;
	int BAnumEliteSites = 10;
	int BAeliteSearchSize = 50;
	int BAnumSelectedSites = 30;
	int BAselectedSearchSize = 10;
	int BAinterations = 1000;

	// Hybrid algorithm parameters
	int HApopsize = 100;
	double HAcrossprob = 0.25;
	double HAmutprob = 0.05;
	int HAnumEliteSites = 10;
	int HAeliteSearchSize = 50;
	int HAnumSelectedSites = 30;
	int HAselectedSearchSize = 10;
	int HAiterations = 1000;

	Result result(evaluator, GApopsize, GAcrossprob, GAmutprob, GAinterations, BApopSize, BAnumEliteSites, BAeliteSearchSize, BAnumSelectedSites,
					BAselectedSearchSize, BAinterations, HApopsize, HAcrossprob, HAmutprob, HAnumEliteSites, HAeliteSearchSize, HAnumSelectedSites,
					HAselectedSearchSize, HAiterations);
	result.runAlgorithms(30);

	return 0;
}