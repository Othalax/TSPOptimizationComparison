#include "ProblemLoader.h"


ProblemLoader::ProblemLoader(const std::string& _filepath)
    : filepath(filepath) {
}

ProblemData ProblemLoader::loadProblem() {
    ProblemData problemdata;

    parseTSPFile(filepath, problemdata);

    return problemdata;
}

void ProblemLoader::parseTSPFile(const std::string& _filepath, ProblemData& _problemdata)
{
    std::ifstream file;
    try {
        file.open(_filepath);
        if (!file.is_open()) {
            throw std::invalid_argument("Error: Cannot open file: " + _filepath);
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
            _problemdata.setDimension(dim);
        }
        else if (token == "EDGE_WEIGHT_TYPE") {
            std::string type;
            file >> colon >> type;
            _problemdata.setEdgeWeightType(type);
        }
        else if (token == "NODE_COORD_SECTION") {
            parseNodeCoordSection(file, _problemdata);
        }
    }

    file.close();

    if (_problemdata.isDataIncomplete())
    {
        throw std::invalid_argument("Error: Something wrong with the file");
    }

}

void ProblemLoader::parseNodeCoordSection(std::ifstream& _file, ProblemData& _problemdata) {
    int dimension = _problemdata.getDimension();
    std::vector<Coordinate> coordinates(dimension);

    int id;
    double x, y;

    for (int i = 0; i < dimension; ++i) {
        _file >> id >> x >> y;
        if (id >= 1 && id <= dimension) {
            coordinates[id - 1] = Coordinate(x, y);
        }
    }

    _problemdata.setCoordinates(coordinates);
}