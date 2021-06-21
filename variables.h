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
#include <regex>
#include <sstream>
#include <iomanip>
#include "companies.h"
#include "user.h"

/* Extern global vars */
extern std::vector <Company> companiesList;
extern void gameLoop();
extern void startGame();
extern void backgroundTimer(double &userMoney, bool running);
extern User user;

/* Namespace for file/string functions - definitions in source.cpp*/
namespace fileStringOperations 
{
	 int strToInt(std::string inputString);
	 int lineCount(std::ifstream inputFile);
	 std::vector<std::string> separateString(std::string input, char delimiter);
	 std::string padRight(std::string str, int size);
	 std::string uppercase(std::string str);
	 bool hasNumber(std::string str);
}

/* Namespace for the user-input commands */
namespace textCommands 
{
	void help();
	void buy(int numBuy, std::string numName, double &userMoney);
	void sell(int numSell, std::string numName, double &userMoney);
}

