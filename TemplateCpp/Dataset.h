#include <vector>
#include <string>

#pragma once
class Dataset
{
public:
	Dataset();
	Dataset(std::string filename);
	std::string GetFileName();
private:
	std::string filename;
};

