#include "ProblemData.h"



ProblemData::ProblemData()
    : dimension(0),
    edgeWeightType(""){
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
        if (coordinates.size() != dimension)
        {
            return std::numeric_limits<double>::infinity();
        }
        double dx = coordinates[i].x - coordinates[j].x;
        double dy = coordinates[i].y - coordinates[j].y;
        return sqrt(dx * dx + dy * dy);
    }
    return std::numeric_limits<double>::infinity();
}

bool ProblemData::isDataIncomplete()
{
    return dimension == 0 || edgeWeightType == "" || coordinates.size() != dimension;
}

