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
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

class stocks {
	public:
		std::string companyName;
		int companyStockValue;
		int numberOfStocks;
		float incomePerStock;

		void update();
		void bailout();

		stocks(std::string aName, int startingValue, float startingIncomeStream, int startingNumberOfStocks = 0) {																	//constructor to initialise values for the companies.
			companyName = aName;
			companyStockValue = startingValue;
			numberOfStocks = startingNumberOfStocks;
			incomePerStock = startingIncomeStream;
		}
		/*void update() {
			money += this->incomePerStock * this->numberOfStocks;
		}*/
};


