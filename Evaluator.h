#pragma once

#include "ProblemData.h"
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <iostream>



class Evaluator {
public:
	Evaluator(const ProblemData& _problemdata, int _dimension);

	double evaluate(const std::vector<int>& _route);

	int getSolutionSize() const;

private:
	const ProblemData& problemData;
	int dimension;

	double calculateRouteCost(const std::vector<int>& _route);
};

