#include "ProblemLoader.h"


ProblemLoader::ProblemLoader(const std::string& filepath)
    : filepath(filepath) {
}

ProblemData ProblemLoader::LoadProblem() {
    ProblemData problem_data;

    ParseTSPFile(filepath, problem_data);

    /*int num_customers = problem_data.getNumGroups() - 1;
    std::vector<int> permutation;
    permutation.reserve(num_customers);

    for (int i = 2; i <= num_customers + 1; ++i) {
        permutation.push_back(i);
    }

    std::mt19937 gen(RANDOM_PERMUTATION_SEED);
    shuffle(permutation.begin(), permutation.end(), gen);*/


    return problem_data;
}

void ProblemLoader::ParseTSPFile(const std::string& file_path, ProblemData& problem_data)
{
    std::ifstream file;
    try {
        file.open(file_path);
        if (!file.is_open()) {
            throw std::invalid_argument("Error: Cannot open file: " + file_path);
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    std::string token;
    std::string colon;

    while (file >> token) {
        if (token == "DIMENSION") {
            int dim;
            file >> colon >> dim;
            problem_data.setDimension(dim);
        }
        else if (token == "EDGE_WEIGHT_TYPE") {
            std::string type;
            file >> colon >> type;
            problem_data.setEdgeWeightType(type);
        }
        else if (token == "NODE_COORD_SECTION") {
            ParseNodeCoordSection(file, problem_data);
        }
    }

    file.close();

    if (problem_data.isDataIncomplete())
    {
        throw std::invalid_argument("Error: Something wrong with the file");
    }

}

void ProblemLoader::ParseNodeCoordSection(std::ifstream& file, ProblemData& problem_data) {
    int dimension = problem_data.getDimension();
    std::vector<Coordinate> coordinates(dimension);

    int id;
    double x, y;

    for (int i = 0; i < dimension; ++i) {
        file >> id >> x >> y;
        if (id >= 1 && id <= dimension) {
            coordinates[id - 1] = Coordinate(x, y);
        }
    }

    problem_data.setCoordinates(coordinates);
}