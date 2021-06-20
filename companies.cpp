#include "variables.h"

bool Company::belowZero() {
	if (companyStockValue <= 0) {
		return true;
	}
	else if (incomePerStock <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void User::calculateValue() {
	for (Company _c : companiesList) {
		stocksHeld += _c.numberOfStocks;
		totalValue += _c.numberOfStocks * _c.companyStockValue;
	}
}
