#include "NeighborOperation.h"
#include "Solution.h"
#include <vector>
#include <random>
#include <execution>

using namespace std;

NeighborOperation::NeighborOperation() {}

void InversionMutation(Solution& solution);

void ScrambleMutation(Solution& solution);

Solution makeCrossOver(int crossIndex, Solution& parentA, Solution& parentB);

void NeighborOperation::CrossOver(Solution& solutionA, Solution& solutionB)
{
	Solution offSpring1;	Solution offSpring2;
	random_device rd;		mt19937_64 genI = mt19937_64(rd());
	int length = 100000; // We define the length of gene here
	uniform_int_distribution<int> uid(0, length - 1);

	int crossPoint = uid(genI);
	offSpring1 = makeCrossOver(crossPoint, solutionA, solutionB);
	offSpring2 = makeCrossOver(crossPoint, solutionB, solutionA);

	offSpring1.age = 0;				offSpring2.age = 0;
	solutionA = offSpring1;			solutionB = offSpring2;
}

Solution NeighborOperation::Mutate(Solution solution)
{
	Solution newSolution = solution;
	random_device rd;    mt19937_64 genI(rd());
	int length = 1000;
	uniform_int_distribution<int> uid(0, length - 1);

	// which part will be mutate

	newSolution.age = 0;
	return newSolution;
}

Solution NeighborOperation::RandomGenerate(Dataset& dataset)
{
	Solution newSolution;

	random_device rd;	mt19937_64 genI(rd());
	int length = 1110;	// Which length ?
	uniform_int_distribution<int> uid(0, length);

	// More code to write here

	newSolution.age = 0;
	return newSolution;
}

// Extension Algorithm will be put here

void InversionMutation(Solution& solution)
{
	Solution newSolution = solution;
	random_device rd;	mt19937_64 genI(rd());

	int length = 1000;  // Which length ?
	uniform_int_distribution<int> uid(0, length - 1);

	int left, right;

	do  {
		left = uid(genI); right = uid(genI);
		if (left > right) swap(left, right);
	} while (left == right);
	
	//reverse();
	newSolution.age = 0;
	solution = newSolution;
}

void ScrambleMutation(Solution& solution)
{
	Solution newSolution = solution;
	random_device rd;	mt19937_64 genI(rd());

	int length = 1000;  // Which length ?
	uniform_int_distribution<int> uid(0, length - 1);

	int left, right;

	do {
		left = uid(genI); right = uid(genI);
		if (left > right) swap(left, right);
	} while (left == right);

	//shuffle(, , genI);
	newSolution.age = 0;
	solution = newSolution;
}

Solution makeCrossOver(int crossIndex, Solution& parentA, Solution& parentB)
{
	Solution offspring;
	int length = 10000; // Which length ?
	vector<bool> check(length, false);

	// More code to write here

	offspring.age = 0;
	return offspring;
}
