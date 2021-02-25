#include <vector>
#include <string>
#include <unordered_map>

#pragma once
class StreetCollection
{
public:
	static std::unordered_map<std::string, int> streetID;
	static std::vector<std::string> streetName;
	static int cnt;
};

int StreetCollection::cnt = 0;

