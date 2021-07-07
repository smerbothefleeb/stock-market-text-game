#include "variables.h"
using namespace fileStringOperations;
using namespace textCommands;

std::vector<std::string> positiveNewsEvents, negativeNewsEvents;
std::vector <int> positiveConsequences, negativeConsequences;
std::vector<std::string> lineOutput;
std::string fileOutput = "";
std::string userInput = "";
User user;

/* Open files */
std::fstream companiesData;
std::fstream positiveEvents;
std::fstream negativeEvents;
std::fstream userData;

int main()
{
	/* Open all files */
	openFile(companiesData, "company-data.csv", defaultCompany); companiesData.open("company-data.csv", std::ios::in | std::ios::out);
	openFile(userData, "user-data.csv", defaultUser); userData.open("user-data.csv", std::ios::in | std::ios::out);
	openFile(positiveEvents, "positive-news-events.csv");
	openFile(negativeEvents, "negative-news-events.csv");

	/* Retrieve any data associated with the user & create a new object of User */
	getline(userData, fileOutput);
	lineOutput = separateString(fileOutput, ',');
	user.money = (double)strToInt(lineOutput[0]);
	user.day = strToInt(lineOutput[1]);
	user.calculateValue();

	std::thread t1(gameLoop, std::ref(user.money));
	std::thread t2(backgroundTimer, std::ref(user.day));

	t1.join();
	t2.join();
	return 0;
}


void gameLoop(double userMoney)
{
	running = true;
	srand((unsigned)time(NULL));

	/* Read through files and copy consequences/events/data to vectors*/
	while (getline(positiveEvents, fileOutput))
	{
		lineOutput = separateString(fileOutput, ',');
		positiveConsequences.push_back((int)std::atoi(lineOutput[0].c_str()));
		positiveNewsEvents.push_back(lineOutput[1]);
	}
	lineOutput.clear();

	while (getline(negativeEvents, fileOutput))
	{
		lineOutput = separateString(fileOutput, ',');
		negativeConsequences.push_back((int)std::atoi(lineOutput[0].c_str()));
		negativeNewsEvents.push_back(lineOutput[1]);
	}
	lineOutput.clear();

	while (getline(companiesData, fileOutput))
	{
		/* Line is separated into 5 parts, with each string as the values from each company */
		/* Then creates a new object of Company using the strings, and adds it to the vector */
		/* CompanyNumber, CompanyName, StockValue, NumberOfStocks, MaximumStocks */
		lineOutput = separateString(fileOutput, ',');
		Company _new(strToInt(lineOutput[0]), lineOutput[1], strToInt(lineOutput[2]), strToInt(lineOutput[3]), strToInt(lineOutput[4]));
		companiesList.push_back(_new);
	}
	lineOutput.clear();
	redrawOutput();

	/* Receive user input and invoke relevant function */
	while (uppercase(userInput) != "EXIT")
	{
		std::vector<std::string> multiString;
		running = true;
		getline(std::cin, userInput);
		if (!(userInput == ""))
		{
			multiString = separateString(userInput, ' ');
		}

		if (uppercase(userInput) == "EXIT")
		{
			save(companiesData, userData);
			std::cout << "\n--- Closing! ---" << std::endl;
		}
		else if (uppercase(userInput) == "HELP")
		{
			commandsHelp();
		}
		else if (uppercase(multiString[0]) == "BUY")
		{
			buy(strToInt(multiString[1]), multiString[2], user.money);
		}
		else if (uppercase(multiString[0]) == "SELL")
		{
			sell(strToInt(multiString[1]), multiString[2], user.money);
		}
		else if (uppercase(multiString[0]) == "SAVE")
		{
			save(companiesData, userData);
		}
		else 
		{
			std::cout << "-- Unrecognised command! --" << std::endl;
		}
	}
	running = false;
	return;
}