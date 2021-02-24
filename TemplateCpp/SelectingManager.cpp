#include "SelectingManager.h"
#include "Solution.h"

#include <vector>
#include <algorithm>
#include <execution>
#include <random>

using namespace std;

SelectingManager::SelectingManager() {
	this->population = vector<Solution>();
}

void SelectingManager::UpdateRouletteWheel(std::vector<Solution>& population)
{
	this->population = population;
	int length = (int)this->population.size();
	pWheel = vector<double>(length);

	long long sum = 0;
	for (int i = 0; i < length; i++) {
		pWheel[i] = (double)population[i].score;
	}

	sum = reduce(execution::par_unseq, pWheel.begin(), pWheel.end(), 0);
	transform(execution::par_unseq, pWheel.begin(), pWheel.end(), pWheel.begin(), 
			 [&sum](double a) {
					return (double)a / sum;
			 });
	inclusive_scan(pWheel.begin(), pWheel.end(), pWheel.begin());
	urd = uniform_real_distribution<double>(0.0, pWheel[length - 1]);
}

void SelectingManager::GetTheRandomizedParents(Solution& parentA, Solution& parentB)
{
	random_device rd;		mt19937_64 rng(rd());
	int p1 = lower_bound(pWheel.begin(), pWheel.end(), urd(rng)) - pWheel.begin();
	int p2 = lower_bound(pWheel.begin(), pWheel.end(), urd(rng)) - pWheel.begin();
	
	parentA = this->population[p1];		 parentB = this->population[p2];
}

std::vector<Solution> SelectingManager::SurvivorSelection(std::vector<Solution>& parents, 
														  std::vector<Solution>& offsprings, 
														  int desiredPopulationSize)
{
	const int LIMIT_AGE = 10;
	vector<Solution> newGeneration;
	random_device rd; 

	for (Solution p : parents) {
		if (p.age < LIMIT_AGE) {
			newGeneration.push_back(p);
		}
	}
	for (Solution child : offsprings) {
		newGeneration.push_back(child);
	}
	sort(execution::par ,newGeneration.begin(), newGeneration.end());
	newGeneration.resize(desiredPopulationSize);
	shuffle(newGeneration.begin(), newGeneration.end(), mt19937_64(rd()));
	return newGeneration;
}
