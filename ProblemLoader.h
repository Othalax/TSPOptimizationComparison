#pragma once

#include "ProblemData.h"
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>



class ProblemLoader {
public:
	ProblemLoader(const std::string& _filepath);

	ProblemData loadProblem();

private:
	std::string filepath;

	void parseTSPFile(const std::string& _filepath, ProblemData& _problemdata);
	void parseNodeCoordSection(std::ifstream& _file, ProblemData& _problemdata);
};

