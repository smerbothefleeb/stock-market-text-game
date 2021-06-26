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

/* Every 60 seconds, start a new day, with periodic updates of the time */
void backgroundTimer(double& userMoney)//, bool running)
{
	//while (running)
	//{
		for (int i = 0; i < 60; i++)
		{
			Sleep(1000);
			userMoney += 1;
			std::cout << "\nDay: " << userMoney << "\n";
			switch (i)
			{
			case 15:
				std::cout << "\n45 seconds left in the day\n";
				break;
			case 30:
				std::cout << "\n30 seconds left in the day\n";
				break;
			case 45:
				std::cout << "\n15 seconds left in the day\n";
				break;
			case 60:
				std::cout << "\nDay: " << userMoney << "\n";
			}
		}
	//}
}