#include "ProblemData.h"
#include <iostream>



ProblemData::ProblemData()
    : dimension(0),
    edgeWeightType("")
{
}

int ProblemData::getDimension() const
{
    return dimension;
}

std::string ProblemData::getEdgeWeightType() const
{
    return edgeWeightType;
}

void ProblemData::setDimension(int _dimension)
{
    dimension = _dimension;
    coordinates.resize(dimension);
}

void ProblemData::setEdgeWeightType(const std::string& _type)
{
    edgeWeightType = _type;
}

void ProblemData::setCoordinates(const std::vector<Coordinate>& _coordinates)
{
    coordinates = _coordinates;
    calculateDistanceMatrix();
}

void ProblemData::setName(std::string _name)
{
    name = _name;
}

double ProblemData::calculateDistance(int i, int j) const {
    if (i < 0 || i >= dimension || j < 0 || j >= dimension) {
        return std::numeric_limits<double>::infinity();
    }
    if (i == j)
        return 0.0;
    if (edgeWeightType == "EUC_2D") {
		double distance = distanceMatrix[i][j];
		return distance;
    }
    return std::numeric_limits<double>::infinity();
}

bool ProblemData::isDataIncomplete()
{
    return dimension == 0 || edgeWeightType == "" || coordinates.size() != dimension;
}

void ProblemData::calculateDistanceMatrix() 
{
    distanceMatrix.resize(dimension, std::vector<double>(dimension, 0.0));
    for (int i = 0; i < dimension; ++i) {
        for (int j = i + 1; j < dimension; ++j) {
            double dx = coordinates[i].x - coordinates[j].x;
            double dy = coordinates[i].y - coordinates[j].y;
            double dist = sqrt(dx * dx + dy * dy);
            distanceMatrix[i][j] = dist;
            distanceMatrix[j][i] = dist;
        }
	}
}

