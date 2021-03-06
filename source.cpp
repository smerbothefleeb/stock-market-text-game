#include "variables.h"
std::vector <Company> companiesList;
bool running = true;
std::mutex accessLock;



namespace fileStringOperations 
{
	/* Convert string to const char* then int with atoi()*/
	int strToInt(std::string inputString) {
		return std::atoi(inputString.c_str());
	}

	/* Count the number of lines in a file */
	int lineCount(std::ifstream inputFile) 
	{
		int numLine = 0;
		std::string line = "";
		while (getline(inputFile, line)) 
		{
			if (!(line.empty())) 
			{
				numLine++;
			}
		}
		return numLine;
	}
	
	/* Parse a delimited string into multiple smaller strings using a given delimiter, then add strings to output vector*/
	std::vector<std::string> separateString(std::string input, char delimiter) 
	{
		std::vector<std::string> output;
		std::stringstream ss(input);
		std::string stringSection;

		while (getline(ss, stringSection, delimiter)) 
		{
			output.push_back(stringSection);
		}
		return output;
	}

	/* If the length of the string is less than the desired size, pad with spaces until it is */
	std::string padRight(std::string str, int size) 
	{
		if (str.size() < size) 
		{
			str = str + std::string(size - str.size(), ' ');
		}
		return str;
	}

	/* Takes a string and returns a capitalised version of it */
	std::string uppercase(std::string& str) 
	{
		for (int i = 0; i < str.size(); i++) 
		{
			str[i] = char(toupper((int)str[i]));
		}
		return str;
	}

	/* Checks through a string and tests every digit to find a number*/
	bool hasNumber(std::string str) 
	{
		for (const char _c : str) 
		{
			if (std::isdigit(_c) == 0) 
			{
				return false;
			}
		}
		return true;
	}

	bool fileExists(const std::string name) 
	{
		std::fstream file(name.c_str());
		return file.is_open();
	}

	void openFile(std::fstream& file, const std::string name, const std::string defaultData)
	{
		if (!(fileExists(name))) 
		{
			std::cout << "File: " << name << " does not exist. Creating..." << std::endl;
			std::fstream temp(name.c_str(), std::ios::out);
			if (temp.is_open())
			{
				std::cout << "File created!" << std::endl;
				temp.write(defaultData.c_str(), defaultData.size());
				temp.close();
			}
			else
			{
				std::cout << "File creation failed!" << std::endl;
			}
		}
	}
}

namespace textCommands 
{
	/* List the available commands */
	void commandsHelp()
	{
		std::cout << "List of commands: \n\n" <<
			" - buy {x} [Company]/[Number] - Buy x quantity of stocks in Company - Use name or number\n" <<
			" - sell {x} [Company]/[Number] - Sell x quantity of stocks in Company - Use name or number\n" <<
			" - save - Save all data to respective files \n" <<
			" - skip - Skip the day and move to the next\n" <<
			" - exit - Immediately exit and save \n";
	}

	/* If the user has enough money, buy the specified number of stocks */
	void buy(const int numBuy, std::string numName, double &userMoney) 
	{
		/* If the call uses the company name */
		if (fileStringOperations::hasNumber(numName) == false) 
		{
			for (int i = 0; i < companiesList.size(); i++) 
			{
				if (fileStringOperations::uppercase(companiesList[i].companyName) == fileStringOperations::uppercase(numName)) 
				{
					if (userMoney >= (numBuy * companiesList[i].companyStockValue)) 
					{
						companiesList[i].changeQuantity(numBuy, userMoney);
						std::cout << numBuy << " stocks bought of " + companiesList[i].companyName + "(" +
							std::to_string(companiesList[i].companyNumber) + ") at \x9C" <<
							companiesList[i].companyStockValue << " each\nTotal expenditure: \x9C" <<
							(companiesList[i].companyStockValue * numBuy) << ". Remaining balance: \x9C" << userMoney << std::endl;
					}

					else 
					{
						std::cout << "-- Cannot buy stocks -- Not enough money! --\n";
						std::cout << "-- You have: \x9C" << userMoney << " and you need \x9C" <<
							(numBuy * companiesList[i].companyStockValue) - userMoney << " more. --" << std::endl;
					}

				}
			}
		} 

		/* If the call uses the company number */
		else 
		{
			for (int i = 0; i < companiesList.size(); i++) 
			{
				if (companiesList[i].companyNumber == fileStringOperations::strToInt(numName)) 
				{
					if (userMoney >= (numBuy * companiesList[i].companyStockValue)) 
					{
						companiesList[i].changeQuantity(numBuy, userMoney);
						std::cout << numBuy << " stocks bought of " + companiesList[i].companyName + "(" +
							std::to_string(companiesList[i].companyNumber) + ") at \x9C" <<
							companiesList[i].companyStockValue << " each\nTotal expenditure: \x9C" <<
							(companiesList[i].companyStockValue * numBuy) << ". Remaining balance: \x9C" << userMoney << std::endl;
					}

					else 
					{
						std::cout << "-- Cannot buy stocks -- Not enough money! --\n";
						std::cout << "-- You have: \x9C" << userMoney << " and you need \x9C" <<
							(numBuy * companiesList[i].companyStockValue) - userMoney << " more. --" << std::endl;
					}
				}
			}
		}
	}

	/* If the user has enough stocks to sell, sell the required amount */
	void sell(const int numSell, std::string numName, double &userMoney) 
	{
		/* If the call uses the company name */
		if (fileStringOperations::hasNumber(numName) == false) 
		{
			for (int i = 0; i < companiesList.size(); i++) 
			{
				if (fileStringOperations::uppercase(companiesList[i].companyName) == fileStringOperations::uppercase(numName)) 
				{
					if (numSell <= companiesList[i].numberOfStocks) 
					{
						companiesList[i].changeQuantity(-numSell, userMoney);
						std::cout << numSell << " stocks sold of " + companiesList[i].companyName + "(" +
							std::to_string(companiesList[i].companyNumber) + ") at \x9C" <<
							companiesList[i].companyStockValue << " each\nTotal earnings: \x9C" <<
							(companiesList[i].companyStockValue * numSell) << ". New balance: \x9C" << userMoney << std::endl;
					}

					else
					{
						std::cout << "-- Cannot sell stocks -- Not enough stocks to sell! --\n" <<
						"-- You have: " << companiesList[i].numberOfStocks << " and you need " << numSell - companiesList[i].numberOfStocks << " more. --" << std::endl;
					}

				}
			}
		}

		/* If the call uses the company number */
		else 
		{
			for (int i = 0; i < companiesList.size(); i++) 
			{
				if (companiesList[i].companyNumber == fileStringOperations::strToInt(numName))
				{
					if (numSell <= companiesList[i].numberOfStocks) 
					{
						companiesList[i].changeQuantity(-numSell, userMoney);
						std::cout << numSell << " stocks sold of " + companiesList[i].companyName + "(" +
							std::to_string(companiesList[i].companyNumber) + ") at \x9C" <<
							companiesList[i].companyStockValue << " each\nTotal earnings: \x9C" <<
							(companiesList[i].companyStockValue * numSell) << ". New balance: \x9C" << userMoney << "\n";
					}

					else 
					{
						std::cout << "-- Cannot sell stocks -- Not enough stocks to sell! --\n" <<
						"-- You have: " << companiesList[i].numberOfStocks << " and you need " << numSell - companiesList[i].numberOfStocks << " more. --" << std::endl;
					}
				}
			}
		}
	}

	void save(std::fstream &_companyData, std::fstream &_userData) 
	{
		/* Save company data */
		_companyData.close();
		std::ofstream companyTemp("company-data.csv", std::ios::out | std::ios::trunc);
		for (Company _c : companiesList)
		{
			companyTemp << std::to_string(_c.companyNumber) + "," + _c.companyName + "," +
				std::to_string(_c.companyStockValue) + "," + std::to_string(_c.numberOfStocks) + "," + std::to_string(_c.maximumStocks) + "\n";
		}
		companyTemp.close();
		_companyData.open("company-data.csv");

		/* Save user data */
		_userData.close();
		std::ofstream userTemp("user-data.csv", std::ios::out | std::ios::trunc);
		userTemp << std::to_string(user.money) + "," + std::to_string(user.day);
		userTemp.close();
		_userData.open("company-data.csv");
		std::cout << "Saved data!" << std::endl;
	}
	
	/* Will be used to skip a day and update the stock values */
	void skipDay() 
	{
		redrawOutput();
	}

}	

/* Clear window, then list companies and their current values, and print user's money and current day */
void redrawOutput() 
{
	system("CLS");
	using namespace fileStringOperations;
	std::cout << "Number       Name              Stock Value       Stocks Held       Maximum Stocks" <<
		std::string(10, ' ') + "Money: " + std::to_string(user.money) + "\n" <<
		std::string(91, ' ') + "Day: " + std::to_string(user.day) + "\n" <<
		std::string(120, '-') << std::endl;

	for (Company i_company : companiesList)
	{
		std::cout << "  " << fileStringOperations::padRight((std::to_string(i_company.companyNumber)), 11) <<
			fileStringOperations::padRight(i_company.companyName, 18) << fileStringOperations::padRight(std::to_string(i_company.companyStockValue), 18) <<
			padRight(std::to_string(i_company.numberOfStocks), 18) << i_company.maximumStocks << std::endl;
	}
	std::cout << "\n" << std::string(120, '-');
	textCommands::commandsHelp();
	std::cout << "Enter Command: ";
}

/* Every 60 seconds, start a new day, with periodic updates of the time */
void backgroundTimer(double userDay)
{
	while (running) 
	{
		for (int i = 0; i <= 60; i++)
		{
			if (running) 
			{
				Sleep(1000);
				//accessLock.lock();
				switch (i)
				{
				case 15:
					std::cout << "\n45 seconds left in the day" << std::endl;
					break;
				case 30:
					std::cout << "30 seconds left in the day" << std::endl;
					break;
				case 45:
					std::cout << "15 seconds left in the day" << std::endl;
					break;
				case 60:
					userDay += 1;
					std::cout << "Day: " << userDay << std::endl;
					break;
				}
				//accessLock.unlock();
			}
			else 
			{
				return;
			}
		}
	}
}