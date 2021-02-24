#pragma region Include the Self Header file
#include "Solver.h"
#include "Scoring.h"
#include "Timer.h"
#include "NeighborOperation.h"
#include "SelectingManager.h"
#include "Parser.h"
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
#include "thrust_useful_function.h"
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
uniform_real_distribution<double> mutationRate(0.05, 0.1);
uniform_real_distribution<double> crossoverRate(0.8, 0.95);
uniform_int_distribution<int> uid;
mt19937_64 rng;
#pragma endregion

Solution solveByAdvancedGA(Dataset& dataset)
{
#pragma region Initialize Class And Setting
	mutex mtx; 
	const int POPULATION_SIZE = 200;
	const int GENERATION = 10000;

#pragma region Initialize Class (Not touch)
	Scoring scoring;	Parser parser;
	SelectingManager selectingManager;
	NeighborOperation neighborOperation;
	Timer timer;		int seconds;
#pragma endregion
	 
#pragma endregion

#pragma region Declare a population and best solution score
	vector<Solution> population;
	Solution bestSolution;
	bestSolution.score = LLONG_MIN;
#pragma endregion

#pragma region Read the previous solutions from previous run
	population = parser.ReadSolutionsFromPreviousRun(dataset);
#pragma endregion

#pragma region Initialize the population for genetic algorithm
	int i = population.size();

	threadPool.parallelize_loop(i, POPULATION_SIZE, [&neighborOperation,
													&population, &mtx,
													&dataset] (int index) 
	{
			Solution solution = neighborOperation.RandomGenerate(dataset);
			lock_guard<mutex> lck(mtx);
			population.push_back(solution);
	});

	//for (int i = population.size(); i < POPULATION_SIZE; i++) 
	//{
	//	Solution solution = neighborOperation.RandomGenerate(dataset);
	//	population.push_back(solution);
	//}
#pragma endregion

#pragma region Set the timer for GA
	int length = 0; // Which length
	seconds = 60;
#pragma endregion

#pragma region Calculate the score of population
	transform(execution::par_unseq, population.begin(), population.end(), population.begin(), [&scoring, &dataset](Solution solution) {
		solution.score = scoring.CalculateScore(dataset, solution);
		return solution;
	});
#pragma endregion

#pragma region Initialize the timer and limit if cannot find better solution for a long period
	int NotFindBetterSolution = 0;
	const int LIMIT_TIME_NOT_FIND_BETTER_SOLUTION = 50;
	timer.SetTheTimer(seconds);
#pragma endregion

	long long bestScore = bestSolution.score;

	for (int generation = 0; generation < GENERATION; generation++) 
	{
#pragma region Update best solution, check if time exceeded (not touch)
		bestSolution = reduce(execution::par_unseq,
							  population.begin(), 
							  population.end(), 
							  bestSolution, 
							  [](Solution target, Solution compare) {
				if (target.score < compare.score) return compare;
				return target;
		});

		if (bestSolution.score > bestScore) {
			NotFindBetterSolution = 0;
			bestScore = bestSolution.score;
		}
		else {
			NotFindBetterSolution++;
			if(NotFindBetterSolution > LIMIT_TIME_NOT_FIND_BETTER_SOLUTION) { break; }
		}

		if (timer.CheckTimerFinish()) { break; }
		if (NotFindBetterSolution > 50) { break; }
#pragma endregion

#pragma region Prepare for parents selection, create new generation population
		selectingManager.UpdateRouletteWheel(population);
		vector<Solution> offSprings;
#pragma endregion

#pragma region Choose random couple of parents for cross over
		random_device rdCross;	rng = mt19937_64(rdCross());
		double percentage = crossoverRate(rng);
		int s = POPULATION_SIZE * percentage / 2; // 80 - 95% will from cross Over

		threadPool.parallelize_loop(1, s, 
									[&neighborOperation, 
									&mtx, &offSprings,
									&selectingManager] (int index) 
		{
				Solution offSpring1, OffSpring2;
				selectingManager.GetTheRandomizedParents(offSpring1, OffSpring2);
				neighborOperation.CrossOver(offSpring1, OffSpring2);

				lock_guard<mutex> lck(mtx);
				offSprings.push_back(offSpring1);
				offSprings.push_back(OffSpring2);
		});
#pragma endregion

#pragma region Mutation some parts of new offsprings population
		random_device rdMutate;	 mt19937_64 rng(rdMutate());
		percentage = mutationRate(rng);
		s = offSprings.size() * percentage;

		threadPool.parallelize_loop(1, s, [&neighborOperation,
										   &offSprings, &mtx](int index) 
		{
				random_device rd;		mt19937_64 rng(rd());
				uniform_int_distribution<int> uid(0, offSprings.size() - 1);
				int idx = uid(rng);		Solution solution = offSprings[idx];
				solution = neighborOperation.Mutate(solution);
				lock_guard<mutex> lck(mtx);
				offSprings[idx] = solution;
		});
#pragma endregion

#pragma region Generating offsprings for diversity
		s = POPULATION_SIZE * 0.25;
		threadPool.parallelize_loop(1, s, 
									[&neighborOperation,
									&offSprings, &mtx,
									&dataset](int index) 
		{
				Solution offSpring = neighborOperation.RandomGenerate(dataset);
				lock_guard<mutex> lck(mtx);
				offSprings.push_back(offSpring);
		});
#pragma endregion

#pragma region Calculate the score of offsprings population
		transform(execution::par_unseq, 
				  offSprings.begin(), offSprings.end(), 
				  offSprings.begin(), [&scoring, &dataset](Solution solution) {
			solution.score = scoring.CalculateScore(dataset, solution);
			return solution;
		});
#pragma endregion

#pragma region Survival Selection for the next generation, update the population
		vector<Solution> newGeneration;
		newGeneration = selectingManager.SurvivorSelection(population, 
														   offSprings, 
														   POPULATION_SIZE);
		population.swap(newGeneration);
#pragma endregion

	}
	return bestSolution;
}
