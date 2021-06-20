#include "variables.h"
using namespace fileStringOperations;
std::vector<std::string> positiveNewsEvents, negativeNewsEvents;
std::vector <int> positiveConsequences, negativeConsequences;
std::vector<std::string> lineOutput;
std::string fileOutput = "";
std::string userInput = "";


int main() {
	srand((unsigned)time(NULL));			

	/* Open files */
	std::ifstream companiesData("company-data.csv");
	std::ifstream positiveEvents("positive-news-events.csv");
	std::ifstream negativeEvents("negative-news-events.csv");
	std::ifstream userData("user-data.csv");


	/* Read through files and copy consequences/events/data to vectors*/
	while (getline(positiveEvents, fileOutput)) {	
		lineOutput = separateString(fileOutput, ',');
		positiveConsequences.push_back((int)std::atoi(lineOutput[0].c_str()));
		positiveNewsEvents.push_back(fileOutput);
	}
	lineOutput.clear();

	while (getline(negativeEvents, fileOutput)) {
		lineOutput = separateString(fileOutput, ',');
		negativeConsequences.push_back((int)std::atoi(lineOutput[0].c_str()));
		negativeNewsEvents.push_back(fileOutput);
	}
	lineOutput.clear();

	while (getline(companiesData, fileOutput)) {
		/* Line is separated into 5 parts, with each string as the values from each company */
		/* Then creates a new object of Company using the strings, and adds it to the vector */
		/* CompanyNumber, CompanyName, StockValue, NumberOfStocks, MaximumStocks */

		lineOutput = separateString(fileOutput, ',');
		Company _new(strToInt(lineOutput[0]), lineOutput[1], strToInt(lineOutput[2]), strToInt(lineOutput[3]), strToInt(lineOutput[4]));
		companiesList.push_back(_new);
	}
	lineOutput.clear();


	/* Retrieve any data associated with the user & create a new object of User */
	getline(userData, fileOutput);
	lineOutput = separateString(fileOutput, ',');
	User user((double)strToInt(lineOutput[0]), strToInt(lineOutput[1]));
	user.calculateValue();

	/* List companies and their current values */
	std::cout << "Number       Name              Stock Value       Stocks Held       Maximum Stocks" <<
		std::string(10, ' ') + "Money: " + std::to_string(user.money) + "\n" <<
		std::string(91, ' ') + "Day: " + std::to_string(user.day) + "\n" <<
		std::string(120, '-') << "\n\n";

	for (Company i_company : companiesList) {
		std::cout << "  " << padRight((std::to_string(i_company.companyNumber)), 11) <<
			padRight(i_company.companyName, 18) << padRight(std::to_string(i_company.companyStockValue), 18) <<
			padRight(std::to_string(i_company.numberOfStocks), 18) << i_company.maximumStocks << "\n";
	}
	std::cout << "\n" << std::string(120, '-');
	textCommands::help();
	std::cout << "Enter command: ";


	/* Receive user input and invoke relevant function */
	getline(std::cin, userInput);
	std::vector<std::string> multiString = separateString(userInput, ' ');

	if (uppercase(userInput) == "HELP") {
		textCommands::help();

	}
	else if (uppercase(multiString[0]) == "BUY") {
		/* String is in 3 sections - The command, number of stocks, and the company/number*/
		textCommands::buy(strToInt(multiString[1]), multiString[2], user.money);
	}
	else if (uppercase(multiString[0]) == "SELL") {
		textCommands::sell(strToInt(multiString[1]), multiString[2], user.money);
	}
}
