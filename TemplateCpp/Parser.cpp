#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include "Dataset.h"
#include "Parser.h"
#include "StreetCollection.h"

using namespace std;
namespace fs = std::filesystem;

Parser::Parser()
{
}

Dataset Parser::GetDataFromStream(std::string filepath, std::string filename)
{
#pragma region The stable code (not touch), use fin for reading input
	ifstream fin(filename);    fin.sync_with_stdio(false);   fin.tie(NULL);
#pragma endregion

	Dataset dataset = Dataset(filename); // Example: fin >> n (reading n from "fin" stream)
	StreetCollection streetColection;
	int duration, intersection, street, vehicle, bonusPoint;
	
	fin >> duration >> intersection >> street >> vehicle >>bonusPoint;

	dataset.duration = duration;
	dataset.intersection = intersection;
	dataset.street = street;
	dataset.vehicle = vehicle;
	dataset.finishPoint = bonusPoint;

	for (int i = 0; i < street; i++) 
	{
		int begin, end, length;
		string name;
		Street street;

		fin >> begin >> end >> name >> length;
		street.begin = begin;
		street.end = end;
		street.name = name;
		street.time = length;
		dataset.streets.push_back(street);
	}

	for (int i = 0; i < vehicle; i++) 
	{
		int path; string name;
		Vehicle vehicle;
		fin >> path;
		vehicle.path = path;

		for (int j = 0; j < path; j++) 
		{
			fin >> name;
			vehicle.paths.push_back(name);
		}
	}
	return dataset;
}

std::vector<Solution> Parser::ReadSolutionsFromPreviousRun(Dataset& dataset)
{
#pragma region Stable code (not touch)
	stringstream ss; ss.sync_with_stdio(false); ss.tie(NULL);
	string file, outputFolder = "output";
	vector<Solution> solutions;
	ss << dataset.GetFileName() << ".out"; ss >> file;
#pragma endregion

	for (auto& p : fs::directory_iterator(outputFolder)) {
		string path = p.path().generic_string();
		path += "/" + file;
		fs::path check = fs::path(path);

		if (fs::exists(check)) {
			Solution solution = ReadSolutionFromFile(path, dataset);
			solutions.push_back(solution);
		}
	}
	return solutions;
}

Solution Parser::ReadSolutionFromFile(std::string filepath, Dataset& dataset)
{
#pragma region Initialize the reading file (Not touch)
	ifstream fin(filepath);			Solution solution;
	fin.sync_with_stdio(false);		fin.tie(NULL);
#pragma endregion

	solution.age = 0;
	return solution;
}
