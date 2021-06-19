#pragma once
#include <iostream>
#include <Windows.h>
#include <thread>
#include <time.h>
#include <string>																																							//default c++ header files
#include <vector>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "companies.h"

/* Namespace for file functions - definitions in source.cpp*/
namespace fileOperations {
	extern int strToInt(std::string inputString);
	extern int lineCount(std::ifstream inputFile);
	extern std::vector<std::string> separateString(std::string input, char delimiter);
}