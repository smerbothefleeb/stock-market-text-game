#include "variables.h"
std::vector <Company> companiesList{};

int strToInt(std::string inputString) {
	/* Convert string to const char* then int */
	return std::atoi(inputString.c_str());
}