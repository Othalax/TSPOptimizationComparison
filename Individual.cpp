#include "Individual.h"


Individual::Individual()
    : fitness(std::numeric_limits<double>::infinity()){
}

Individual::Individual(int size)
    : route(size), fitness(-1.0){
}

Individual::Individual(const Individual& other)
    : route(other.route), fitness(other.fitness) {
}

Individual& Individual::operator=(const Individual& other)
{
    if (this != &other) {
        route = other.route;
        fitness = other.fitness;
    }
    return *this;
}

double Individual::evaluate(Evaluator& evaluator)
{
    fitness = evaluator.evaluate(route);
    return fitness;
}

void Individual::mutate(double mutProb, std::mt19937& rng) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
}

std::pair<Individual*, Individual*> Individual::crossover(const Individual& other, std::mt19937& rng) const
{
    std::uniform_int_distribution<size_t> dist(1, route.size() - 1);
    
    return { NULL, NULL };
}

double Individual::getFitness() const
{
    return fitness;
}

void Individual::setFitness(double fit)
{
    fitness = fit;
}

std::vector<int>* Individual::getGenotype()
{
    return &route;
}
