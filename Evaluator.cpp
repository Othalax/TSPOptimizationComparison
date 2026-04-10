#include "Evaluator.h"



Evaluator::Evaluator(const ProblemData& _problemdata, int _dimension)
    : problemData(_problemdata),
    dimension(_dimension)
{

}

double Evaluator::evaluate(const std::vector<int>& _route) {
	double cost = calculateRouteCost(_route);

    return cost;
}

int Evaluator::getSolutionSize() const
{
	return dimension;
}

double Evaluator::calculateRouteCost(const std::vector<int>& _route) {
    if (_route.empty())
        return 0.0;

	double totalCost = 0.0;

	for (size_t i = 1; i < _route.size(); ++i) {
		totalCost += problemData.calculateDistance(_route[i-1], _route[i]);
	}
	totalCost += problemData.calculateDistance(_route.back(), _route.front());

    return totalCost;
}
