#include "variables.h"
using namespace fileStringOperations;
std::vector<std::string> positiveNewsEvents, negativeNewsEvents;
std::vector <int> positiveConsequences, negativeConsequences;
std::vector <Company> companiesList;
std::vector<std::string> lineOutput;
std::string fileOutput = "";

int main() {
	srand((unsigned)time(NULL));			

	/* Open files */
	std::ifstream companiesData("company-data.csv");
	std::ifstream positiveEvents("positive-news-events.csv");
	std::ifstream negativeEvents("negative-news-events.csv");


	/* Read through files and copy consequences/events to vectors*/
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
		/* CompanyNumber, CompanyName, StockValue, NumberOfStocks, MaximumStocks*/

		lineOutput = separateString(fileOutput, ',');
		Company _new(strToInt(lineOutput[0]), lineOutput[1], strToInt(lineOutput[2]), strToInt(lineOutput[3]), strToInt(lineOutput[4]));
		companiesList.push_back(_new);
	}

	/* List companies and their current values */
	
	std::cout << "Companies retrieved from file: \n\n" <<
		"Number       Name              Stock Value       Stocks Held       Maximum Stocks\n" <<
		"--------------------------------------------------------------------------------------\n\n  ";

	for (Company i_company : companiesList) {
		std::cout << padRight((std::to_string(i_company.companyNumber)), 11) <<
			padRight(i_company.companyName, 18) << padRight(std::to_string(i_company.companyStockValue), 18) <<
			padRight(std::to_string(i_company.numberOfStocks), 18) << i_company.maximumStocks << "\n";
	}
	std::cout << "\n--------------------------------------------------------------------------------------";
}
