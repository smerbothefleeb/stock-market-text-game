#include "variables.h"

std::vector<std::string> positiveNewsEvents, negativeNewsEvents;
std::vector <int> positiveConsequences, negativeConsequences;
std::string fileOutput = "";													
stocks EggCorp("EggCorp", 50, 0.1, 10);											
stocks OrangeLTD("OrangeLTD", 500, 10, 0);

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

	/* Open files and read contents to vectors */
	std::ifstream positiveEvents("positive-news-events.txt");					
	std::ifstream negativeEvents("negative-news-events.txt");

	while (getline(positiveEvents, fileOutput)) {	
		std::vector<std::string> output = separateString(fileOutput, ',');
		positiveConsequences.push_back((int)std::atoi(output[0].c_str()));
		positiveNewsEvents.push_back(fileOutput);
	}
	while (getline(negativeEvents, fileOutput)) {
		std::vector<std::string> output = separateString(fileOutput, ',');
		negativeConsequences.push_back((int)std::atoi(output[0].c_str()));
		negativeNewsEvents.push_back(fileOutput);
	}
	std::cout << negativeConsequences[0] << "  " << negativeNewsEvents[0] << "\n";

}
