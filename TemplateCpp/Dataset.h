#include <vector>
#include <string>


struct Street {
	int begin, end;
	std::string name;
	int time;
};

struct Vehicle {
	int path;
	std::vector<int> paths;
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
private:
	std::string filename;
};

