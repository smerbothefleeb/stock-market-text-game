#include "variables.h"
std::vector <Company> companiesList{};

int strToInt(std::string inputString) {
	/* Convert string to const char* then int */
	return std::atoi(inputString.c_str());
}

int lineCount(std::ifstream inputFile) {
	int numLine = 0;
	std::string line = "";
	while (getline(inputFile, line)) {
		if (!(line.empty())) {
			numLine++;
		}
	}
	return numLine;
}