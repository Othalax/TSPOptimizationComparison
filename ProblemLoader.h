#pragma once

#include "ProblemData.h"
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>



class ProblemLoader {
public:
	ProblemLoader(const std::string& filepath);

	ProblemData LoadProblem();

private:
	std::string filepath;

	void ParseTSPFile(const std::string& file_path, ProblemData& problem_data);
	void ParseEdgeWeightSection(std::ifstream& file, ProblemData& problem_data);
	void ParseNodeCoordSection(std::ifstream& file, ProblemData& problem_data);
	void ParseDemandSection(std::ifstream& file, ProblemData& problem_data);
	void ParseDepotSection(std::ifstream& file, ProblemData& problem_data);
};

