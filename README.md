# A Hybrid of Bees Algorithm and Genetic Algorithm for the Traveling Salesman Problem

## Table of contents

- [Description](#description)
- [Technologies](#technologies)
- [Installation and build](#installation-and-build)
- [Project structure](#project-structure)

## Description

This repository contains the source code for the scientific article "A Hybrid of Bees Algorithm and Genetic Algorithm for the Traveling Salesman Problem" (the full text is available in the included PDF file).

The project introduces a novel hybrid metaheuristic approach and evaluates its performance against the standard Bees Algorithm (BA) and Genetic Algorithm (GA) in solving the Traveling Salesperson Problem (TSP). To achieve optimal routing, the solvers implement specialized evolutionary and swarm mechanics—including tournament selection, ordered crossover, partial shuffle mutation, and a 2-opt local search heuristic. The engine natively supports the TSPLIB benchmark standard, automatically parsing Euclidean (EUC_2D) node coordinates to construct exact distance matrices for fitness evaluation.

## Technologies

- **C++**: Core logic and object-oriented architecture.
- **STL (Standard Template Library)**: Utilized for data management via `std::vector` and algorithm timing via `<chrono>`.
- **Mersenne Twister (MT19937)**: High-quality pseudo-random number generation for genetic diversity and population initialization.

## Installation and build

The project requires a compiler that supports C++11 or higher. Example datasets are located in the `/data` folder; all instances are from the TSPLIB benchmark library.

Inside `main.cpp`, you can adjust the algorithms' parameters and your preferred problem instance. The `Result` class will execute the algorithms across multiple seeds and output the average runtime and fitness for each metaheuristic.

## Project structure

``` bash
src/
├── main.cpp                 # Entry point: sets parameters and triggers the Result class
├── ProblemLoader.h/.cpp     # Parser: reads .tsp files and parses DIMENSION and NODE_COORD_SECTION
├── ProblemData.h/.cpp       # Data Model: stores coordinates and computes the distance matrix
├── Result.h/.cpp            # Benchmark Engine: runs algorithms across multiple seeds and averages time/fitness
├── GeneticAlgorithm.h/.cpp  # GA Engine: manages the population loop using selection, crossover, and mutation
├── BeesAlgorithm.h/.cpp     # BA Engine: manages elite/selected sites and neighborhood searches
├── HybridAlgorithm.h/.cpp   # HA Engine: combines swarm intelligence site searching with evolutionary crossover
├── Individual.h/.cpp        # Solution Model: handles genotypes (routes), ordered crossover, partial shuffle mutation, and 2-opt
└── Evaluator.h/.cpp         # Fitness Function: calculates the total travel cost for a given route sequence
