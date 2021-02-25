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
		inter.id = i;
		inter.numStreet = 0;

		int d = dataset.duration / 2;

		for (int j = 0; j < incomingStreet.size(); ++j) {
			int hasTraffic = rand() % 100 + 1;
			if (hasTraffic >= 50) { // 50% for an incoming street to have a green traffic light
				placedGreenLight = true;
				inter.numStreet++;
				Schedule sche;
				sche.streetName = incomingStreet[j].name;
				sche.time = rand() % d + 1; // random time each traffic between 1 and 50
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
