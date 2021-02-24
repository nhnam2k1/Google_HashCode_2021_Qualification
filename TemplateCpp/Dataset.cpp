#include "Dataset.h"

Dataset::Dataset()
{
}

Dataset::Dataset(std::string filename)
{
	this->filename = filename;
}

std::string Dataset::GetFileName()
{
	return this->filename;
}
