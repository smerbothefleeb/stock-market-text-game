#pragma once

class stocks {
public:
	std::string companyName;
	int companyStockValue;
	int numberOfStocks;
	float incomePerStock;

	void update();
	bool belowZero();

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


