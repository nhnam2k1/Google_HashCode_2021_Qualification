#include <vector>
#include <string>
#include <unordered_map>

#pragma once
class StreetCollection
{
	static std::unordered_map<std::string, int> streetID;
	static std::vector<std::string> streetName;
	static int cnt;
	
	void generateId() {
		for (int i = 0; i < streetName.size(); i++) {
			if (!streetID[streetName[i]]) {
				streetID[streetName[i]] = ++cnt;
			}
		}
	}

};

int StreetCollection::cnt = 0;

