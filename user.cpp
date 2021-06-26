#include "variables.h"

/* Calculate the cumulative value of all the user's stocks */
void User::calculateValue() 
{
	for (Company _c : companiesList) 
	{
		stocksHeld += _c.numberOfStocks;
		totalValue += _c.numberOfStocks * _c.companyStockValue;
	}
}

