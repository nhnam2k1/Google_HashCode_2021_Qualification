#include "Random.h"

Solution Random::generateRandomSolution(Dataset dataset)
{
	Solution sol;
	for (int i = 0; i < dataset.intersection; ++i) {
		std::vector<Street> incomingStreet;
		for (int j = 0; j < dataset.streets.size(); ++j) {
			if (dataset.streets[j].end == i) {
				incomingStreet.push_back(dataset.streets[j]);
			}
		}
		bool placedGreenLight = false;
		Intersection inter;
		inter.numStreet = i;

		for (int j = 0; j < incomingStreet.size(); ++j) {
			int hasTraffic = rand() % 100 + 1;
			if (hasTraffic >= 50) { // 50% for an incoming street to have a green traffic light
				placedGreenLight = true;
				Schedule sche;
				sche.streetName = incomingStreet[j].name;
				sche.time = rand() % 50 + 1; // random time each traffic between 1 and 50
				inter.schedules.push_back(sche);
			}
		}
		if (placedGreenLight) {
			sol.numIntersection++;
			sol.intersections.push_back(inter);
		}
	}
	return sol;
}
