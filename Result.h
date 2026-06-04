#pragma once
#include <chrono>
#include "HybridAlgorithm.h"
#include "GeneticAlgorithm.h"
#include "BeesAlgorithm.h"

class Result
{
public:
	Result(Evaluator& evaluator, int GApopsize, double GAcrossprob, double GAmutprob, int GAinterations, int BApopSize,	int BAnumEliteSites, 
			int BAeliteSearchSize,	int BAnumSelectedSites, int BAselectedSearchSize, int BAinterations, int HApopsize,
			double HAcrossprob, double HAmutprob, int HAnumEliteSites, int HAeliteSearchSize, int HAnumSelectedSites, int HAselectedSearchSize,
			int HAiterations);
	void runAlgorithms(int seednum);
private:
	Evaluator& evaluator;
	int GApopsize;
	double GAcrossprob;
	double GAmutprob;
	int GAinterations;
	int BApopSize;
	int BAnumEliteSites;
	int BAeliteSearchSize;
	int BAnumSelectedSites;
	int BAselectedSearchSize;
	int BAinterations;
	int HApopsize;
	double HAcrossprob;
	double HAmutprob;
	int HAnumEliteSites;
	int HAeliteSearchSize;
	int HAnumSelectedSites;
	int HAselectedSearchSize;
	int HAiterations;
};

