#include "variables.h"
std::vector<std::string> positiveNewsEvents, negativeNewsEvents;
std::vector <int> positiveConsequences, negativeConsequences;
std::vector<std::string> lineOutput;
std::string fileOutput = "";

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
	std::vector<std::string> output;
	std::stringstream ss(input);
	std::string stringSection;

	while (getline(ss, stringSection, delimiter)) {
		output.push_back(stringSection);
	}
	return output;
}

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
		lineOutput = separateString(fileOutput, ',');
		Company _new(strToInt(lineOutput[0]), lineOutput[1], strToInt(lineOutput[2]), strToInt(lineOutput[3]), strToInt(lineOutput[4]));
		companiesList.push_back(_new);
	}
}
