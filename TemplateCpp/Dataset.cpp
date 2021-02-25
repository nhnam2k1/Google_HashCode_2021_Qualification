#include "Dataset.h"

Dataset::Dataset()
{
	
}

Dataset::Dataset(std::string filename)
{
	this->filename = filename;
	this->streets = std::vector<Street>();
	this->vehicles = std::vector<Vehicle>();

}

std::string Dataset::GetFileName()
{
	return this->filename;
}
