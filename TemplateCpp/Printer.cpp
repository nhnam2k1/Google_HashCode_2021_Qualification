#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include "Printer.h"
#include "Solution.h"

using namespace std;
namespace fs = std::filesystem;

Printer::Printer()
{
	this->current_time = time(NULL);
}

void Printer::PrintSolution(Solution& solution, std::string filename)
{
#pragma region The stable code (not touch), use fout for output normal
	stringstream ss; ss.sync_with_stdio(false); ss.tie(NULL);
	
	ss << "output/" << this->current_time << "/";
	string outputFile;			ss >> outputFile;

	fs::create_directory(outputFile);
	outputFile = outputFile + filename + ".out";

	ofstream fout(outputFile);   fout.sync_with_stdio(false);  fout.tie(NULL);
#pragma endregion

	
	
}