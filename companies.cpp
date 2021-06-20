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

void Company::changeQuantity(int amount, double &userMoney) {
	userMoney -= (numberOfStocks * companyStockValue);
	numberOfStocks += amount;
}
