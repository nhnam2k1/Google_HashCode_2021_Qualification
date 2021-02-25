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

	StreetCollection() {

	}
	
	void generateId() {
		for (int i = 0; i < streetName.size(); i++) {
			if (!streetID[streetName[i]]) {
				streetID[streetName[i]] = ++cnt;
			}
		}
	}

};

int StreetCollection::cnt = 0;

