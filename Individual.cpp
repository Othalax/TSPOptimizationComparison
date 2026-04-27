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

// Reverse Sequence Mutation
void Individual::mutate(std::mt19937& rng) {
    int n = route.size();
    std::vector<int> mutated(n);

    std::uniform_int_distribution<int> dist(0, n - 1);
    int start = dist(rng);
    int end = dist(rng);
    while (start == end)
    {
		end = dist(rng);
    }
    if (start > end) std::swap(start, end);

    for (int i = 0; i < n; ++i) {
        if (i >= start && i <= end) {
            mutated[i] = route[start + end - i];
        } else {
            mutated[i] = route[i];
        }
    }

    route = std::move(mutated);
}

void Individual::randomize()
{
    int n = route.size();
    for (int i = 0; i < n; ++i) {
        route[i] = i;
    }
	std::shuffle(route.begin(), route.end(), std::mt19937(std::random_device()()));
}

// Ordered Crossover
std::pair<Individual, Individual> Individual::crossover(const Individual& other, std::mt19937& rng) const
{
    int n = route.size();
    std::vector<int> child1(n, -1);
    std::vector<int> child2(n, -1);

    std::uniform_int_distribution<int> dist(0, n - 1);
    int start = dist(rng);
    int end = dist(rng);
    if (start > end) std::swap(start, end);

    std::vector<bool> inChild1(n + 1, false); 
    std::vector<bool> inChild2(n + 1, false);

    for (int i = start; i <= end; ++i)
    {
        child1[i] = route[i];
        inChild1[route[i]] = true;

        child2[i] = other.route[i];
        inChild2[other.route[i]] = true;
    }

    for (int i = 0, j = 0, k = 0; i < n; ++i) {
        if (!inChild1[other.route[i]]) {
            while (child1[j] != -1) ++j;
            child1[j] = other.route[i];
            inChild1[other.route[i]] = true;
        }
        if (!inChild2[route[i]]) {
            while (child2[k] != -1) ++k;
            child2[k] = route[i];
            inChild2[route[i]] = true;
        }
	}

    return std::pair<Individual, Individual>(Individual(child1), Individual(child2));
}

// 2-opt Local Search
void Individual::neighborhoodSearch(Evaluator& evaluator, std::mt19937& rng)
{
    std::uniform_int_distribution<int> dist(0, route.size() - 1);
    int i = dist(rng);
    int j = dist(rng);

    if (i > j) std::swap(i, j);

    std::reverse(route.begin() + i, route.begin() + j);
	evaluate(evaluator);
}

// Edge Recombination Crossover
//Individual Individual::crossover(const Individual& other, std::mt19937& rng) const
//{
//    int n = route.size();
//    std::vector<std::set<int>> adj(n);
//    auto addNeighbors = [&](const std::vector<int>& p) 
//    {
//        for (int i = 0; i < n; ++i) 
//        {
//            int left = p[(i - 1 + n) % n];
//            int right = p[(i + 1) % n];
//            adj[p[i]].insert(left);
//            adj[p[i]].insert(right);
//        }
//    };
//
//    addNeighbors(this->route);
//    addNeighbors(other.route);
//
//    std::vector<int> childPath;
//    childPath.reserve(n);
//    std::vector<bool> visited(n, false);
//
//    std::uniform_int_distribution<int> distBinary(0, 1);
//    int currentCity = (distBinary(rng) == 0) ? this->route[0] : other.route[0];
//
//    while (childPath.size() < n) 
//    {
//        childPath.push_back(currentCity);
//        visited[currentCity] = true;
//
//        for (int neighbor : adj[currentCity]) 
//        {
//            adj[neighbor].erase(currentCity);
//        }
//
//        const std::set<int>& neighbors = adj[currentCity];
//        int nextCity = -1;
//
//        if (!neighbors.empty()) 
//        {
//            int minNeighbors = 5; 
//            std::vector<int> candidates;
//
//            for (int neighbor : neighbors) 
//            {
//                int count = adj[neighbor].size();
//                if (count < minNeighbors) 
//                {
//                    minNeighbors = count;
//                    candidates = { neighbor };
//                }
//                else if (count == minNeighbors) 
//                {
//                    candidates.push_back(neighbor);
//                }
//            }
//
//            std::uniform_int_distribution<int> distCand(0, candidates.size() - 1);
//            nextCity = candidates[distCand(rng)];
//        }
//        else 
//        {
//            std::vector<int> unvisited;
//            for (int i = 0; i < n; ++i) 
//            {
//                if (!visited[i]) unvisited.push_back(i);
//            }
//
//            if (!unvisited.empty()) 
//            {
//                std::uniform_int_distribution<int> distUnv(0, unvisited.size() - 1);
//                nextCity = unvisited[distUnv(rng)];
//            }
//        }
//        currentCity = nextCity;
//    }
//
//    return Individual(childPath);
//}

double Individual::getFitness() const
{
    return fitness;
}

std::vector<int>* Individual::getGenotype()
{
    return &route;
}
