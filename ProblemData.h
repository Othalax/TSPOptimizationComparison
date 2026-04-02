#pragma once
#include <cmath>
#include <vector>
#include <string>

constexpr unsigned int RANDOM_PERMUTATION_SEED = 42;
struct Coordinate {
	double x;
	double y;

	Coordinate() : x(0.0), y(0.0) {}
	Coordinate(double x, double y) : x(x), y(y) {}
};

class ProblemData {
public:
	ProblemData();

	int getDimension() const;
	std::string getEdgeWeightType() const;
	int getNumGroups() const;

	void setDimension(int _dimension);
	void setEdgeWeightType(const std::string& _type);
	void setNumGroups(int _numGroups);
	void setCoordinates(const std::vector<Coordinate>& _coordinates);
	void setName(std::string _name);

	double calculateDistance(int i, int j) const;
	bool isDataIncomplete();
private:
	std::string name;
	int dimension;
	std::string edgeWeightType;
	int numGroups;

	std::vector<Coordinate> coordinates;
};
