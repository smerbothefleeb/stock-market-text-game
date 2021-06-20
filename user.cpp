#include "variables.h"

void User::calculateValue() 
{
	for (Company _c : companiesList) {
		stocksHeld += _c.numberOfStocks;
		totalValue += _c.numberOfStocks * _c.companyStockValue;
	}
}