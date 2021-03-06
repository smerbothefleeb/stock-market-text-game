#include "variables.h"
const std::string defaultCompany = "1, EggCorp, 10, 0, 1000";
/* Check if a certain stock value is less than 0 */
bool Company::belowZero() 
{
	if (companyStockValue <= 0) 
	{
		return true;
	}
	else if (incomePerStock <= 0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

/* Add or take away money by "buying" or "selling" stocks */
void Company::changeQuantity(int amount, double &userMoney) 
{
	userMoney -= (amount * companyStockValue);
	numberOfStocks += amount;
}
