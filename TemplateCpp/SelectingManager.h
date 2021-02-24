#include "Solution.h"
#include <vector>
#include <random>

#pragma once
class SelectingManager
{
public:
	SelectingManager();
	void UpdateRouletteWheel(std::vector<Solution>& population);
	void GetTheRandomizedParents(Solution& parentA, Solution& parentB);
	std::vector<Solution> SurvivorSelection(std::vector<Solution>& parents,
										    std::vector<Solution>& offsprings,
											int desiredPopulationSize);
private:
	std::vector<Solution> population;
	std::vector<double> pWheel;
	std::uniform_real_distribution<double> urd;
};

