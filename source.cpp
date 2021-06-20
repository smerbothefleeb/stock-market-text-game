#include "variables.h"
std::vector <Company> companiesList;

namespace fileStringOperations {

	int strToInt(std::string inputString) {
		/* Convert string to const char* then int with atoi()*/
		return std::atoi(inputString.c_str());
	}

	int lineCount(std::ifstream inputFile) {
		int numLine = 0;
		std::string line = "";
		while (getline(inputFile, line)) {
			if (!(line.empty())) {
				numLine++;
			}
		}
		return numLine;
	}

	std::vector<std::string> separateString(std::string input, char delimiter) {
		/* Parse a delimited string into multiple smaller strings using a given delimiter, then add strings to output vector*/
		std::vector<std::string> output;
		std::stringstream ss(input);
		std::string stringSection;

		while (getline(ss, stringSection, delimiter)) {
			output.push_back(stringSection);
		}
		return output;
	}

	std::string padRight(std::string str, int size) {
		/* If the length of the string is less than the desired size, pad with spaces until it is */
		if (str.size() < size) {
			str = str + std::string(size - str.size(), ' ');
		}
		return str;
	}

	std::string uppercase(std::string str) {
		for (int i = 0; i < str.size(); i++) {
			str[i] = char(toupper((int)str[i]));
		}
		return str;
	}

	bool hasNumber(std::string str) {
		/* Checks through a string and tests every digit to find a number*/
		for (char const _c : str) {
			if (std::isdigit(_c) == 0) {
				return false;
			}
		}
		return true;
	}
}

namespace textCommands {
	void help() {
		std::cout << "\nList of commands: \n\n" <<
			" - buy {x} [Company]/[Number] - Buy x quantity of stocks in Company - Use name or number\n" <<
			" - sell {x} [Company]/[Number] - Sell x quantity of stocks in Company - Use name or number\n" <<
			" - save - Save all data to respective files \n" <<
			" - skip - Skip the day and move to the next\n\n";
	}

	void buy(int numBuy, std::string numName, double userMoney) {
		/* If the call uses the company name */
		if (fileStringOperations::hasNumber(numName) == false) {
			for (int i = 0; i < companiesList.size(); i++) {
				if (fileStringOperations::uppercase(companiesList[i].companyName) == fileStringOperations::uppercase(numName)) {
					companiesList[i].changeQuantity(numBuy, userMoney);
					std::cout << numBuy << " stocks bought of " + companiesList[i].companyName + "(" + 
						std::to_string(companiesList[i].companyNumber) + ") at \x9C" <<
						companiesList[i].companyStockValue << "\nTotal expenditure: \x9C" <<
						(companiesList[i].companyStockValue * numBuy) << ". Remaining balance: \x9C" << userMoney << "\n\n";
				}
			}
		}
		else {
			for (int i = 0; i < companiesList.size(); i++) {
				if (companiesList[i].companyNumber == fileStringOperations::strToInt(numName)) {
					companiesList[i].changeQuantity(numBuy, userMoney);
					std::cout << numBuy << " stocks bought of " + companiesList[i].companyName + "(" +
						std::to_string(companiesList[i].companyNumber) + ") at \x9C" <<
						companiesList[i].companyStockValue << "\nTotal expenditure: \x9C" <<
						(companiesList[i].companyStockValue * numBuy) << ". Remaining balance: \x9C" << userMoney << "\n\n";
				}
			}

		}

	}
}