#include <vector>
#include <string>
#include <unordered_map>

#pragma once
class StreetCollection
{
public:
	 std::unordered_map<std::string, int> streetID;
	std::vector<std::string> streetName;
	int cnt;
};

