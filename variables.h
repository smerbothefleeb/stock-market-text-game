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

#include <allegro5/allegro.h>																																				//allegro header files
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

class stocks {
	public:
		string companyName;
		int companyStockValue;
		int numberOfStocks;
		float incomePerStock;

		void update();
		void bailout();

		stocks(string aName, int startingValue, float startingIncomeStream, int startingNumberOfStocks = 0) {																	//constructor to initialise values for the companies.
			companyName = aName;
			companyStockValue = startingValue;
			numberOfStocks = startingNumberOfStocks;
			incomePerStock = startingIncomeStream;
		}
		void update() {
			money += this->incomePerStock * this->numberOfStocks;
		}
};


