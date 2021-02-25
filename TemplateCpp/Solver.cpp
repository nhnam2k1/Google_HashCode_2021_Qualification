#pragma region Include the Self Header file
#include "Solver.h"
#include "Scoring.h"
#include "Timer.h"
#include "NeighborOperation.h"
#include "SelectingManager.h"
#include "Parser.h"
#include "Random.h"

#pragma endregion

#pragma region Include STL library
#include <math.h>
#include <algorithm>
#include <vector>
#include <execution>
#include <random>
#include <climits>
#include <mutex>
#pragma endregion

// GPU header utility
#include "thread_pool.hpp"

using namespace std;

Solver::Solver() {}

Solution solveByAdvancedGA(Dataset& dataset);

Solution Solver::GetTheSolution(Dataset& dataset)
{
	// This is for the more cases/tools/ideas to solve
	Solution solution = solveByAdvancedGA(dataset);
	return solution;
}

/// <summary>
/// This is the main implementation for the Google Hash Code Problem
/// Calculating from the dataset, and transfer into solution using all 
/// </summary>

// Extending algorithm will start from here

thread_pool threadPool;

#pragma region Declare random generator
//uniform_real_distribution<double> mutationRate(0.05, 0.1);
//uniform_real_distribution<double> crossoverRate(0.8, 0.95);
//uniform_int_distribution<int> uid;
//mt19937_64 rng;
#pragma endregion

Solution solveByAdvancedGA(Dataset& dataset)
{
	Random random;
	Solution solution = random.generateRandomSolution(dataset);
	return solution;
}
