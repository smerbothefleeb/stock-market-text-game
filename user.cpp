#include "variables.h"
const std::string defaultUser = "100,1";

/* Calculate the cumulative value of all the user's stocks */
void User::calculateValue() 
{
	for (Company _c : companiesList) 
	{
		stocksHeld += _c.numberOfStocks;
		totalValue += _c.numberOfStocks * _c.companyStockValue;
	}
}

