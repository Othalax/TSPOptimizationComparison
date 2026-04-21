#include "Individual.h"


Individual::Individual()
    : fitness(std::numeric_limits<double>::infinity())
{
}

Individual::Individual(int size)
    : route(size), fitness(-1.0)
{
}

Individual::Individual(std::vector<int> route)
	: route(std::move(route)), fitness(-1.0)
{
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

void Individual::randomize()
{
    int n = route.size();
    for (int i = 0; i < n; ++i) {
        route[i] = i;
    }
	std::shuffle(route.begin(), route.end(), std::mt19937(std::random_device()()));
}

// Edge Recombination Crossover
Individual Individual::crossover(const Individual& other, std::mt19937& rng) const
{
    int n = route.size();
    std::vector<std::set<int>> adj(n);
    auto addNeighbors = [&](const std::vector<int>& p) 
    {
        for (int i = 0; i < n; ++i) 
        {
            int left = p[(i - 1 + n) % n];
            int right = p[(i + 1) % n];
            adj[p[i]].insert(left);
            adj[p[i]].insert(right);
        }
    };

    addNeighbors(this->route);
    addNeighbors(other.route);

    std::vector<int> childPath;
    childPath.reserve(n);
    std::vector<bool> visited(n, false);

    std::uniform_int_distribution<int> distBinary(0, 1);
    int currentCity = (distBinary(rng) == 0) ? this->route[0] : other.route[0];

    while (childPath.size() < n) 
    {
        childPath.push_back(currentCity);
        visited[currentCity] = true;

        for (int neighbor : adj[currentCity]) 
        {
            adj[neighbor].erase(currentCity);
        }

        const std::set<int>& neighbors = adj[currentCity];
        int nextCity = -1;

        if (!neighbors.empty()) 
        {
            int minNeighbors = 5; 
            std::vector<int> candidates;

            for (int neighbor : neighbors) 
            {
                int count = adj[neighbor].size();
                if (count < minNeighbors) 
                {
                    minNeighbors = count;
                    candidates = { neighbor };
                }
                else if (count == minNeighbors) 
                {
                    candidates.push_back(neighbor);
                }
            }

            std::uniform_int_distribution<int> distCand(0, candidates.size() - 1);
            nextCity = candidates[distCand(rng)];
        }
        else 
        {
            std::vector<int> unvisited;
            for (int i = 0; i < n; ++i) 
            {
                if (!visited[i]) unvisited.push_back(i);
            }

            if (!unvisited.empty()) 
            {
                std::uniform_int_distribution<int> distUnv(0, unvisited.size() - 1);
                nextCity = unvisited[distUnv(rng)];
            }
        }
        currentCity = nextCity;
    }

    return Individual(childPath);
}

double Individual::getFitness() const
{
    return fitness;
}

std::vector<int>* Individual::getGenotype()
{
    return &route;
}
