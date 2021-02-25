#include <vector>
#include <string>
#include "StreetCollection.h"

struct Street {
	int begin, end;
	std::string name;
	int time;
};

struct Vehicle {
	int path;
	std::vector<std::string> paths;
};

#pragma once
class Dataset
{
public:
	Dataset();
	Dataset(std::string filename);
	std::string GetFileName();
	int duration; // D
	int intersection; // I;
	int street; // S
	int vehicle; // V
	int finishPoint; // F
	std::vector<Street> streets;
	std::vector<Vehicle> vehicles;
	StreetCollection collection;
private:
	std::string filename;
};

