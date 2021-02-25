#pragma once
#include <string>
#include <vector>

struct Schedule {
	std::string streetName;
	int time;

};

struct Intersection {
	int id;
	int numStreet;
	std::vector<Schedule> schedules;
};

class Solution
{
public:
	Solution();
	long long score;
	unsigned short int age;
	int numIntersection;
	std::vector<Intersection> intersections;

	bool operator < (const Solution other) const;
private:
};

