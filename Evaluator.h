#pragma once

#include "ProblemData.h"

class Evaluator
{
	public:
		Evaluator(ProblemData& _problemData);

	private:
		int lowerBound;
		int upperBound;
};

