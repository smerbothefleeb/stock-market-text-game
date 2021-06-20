#include "variables.h"
std::vector <Company> companiesList;
User user(100);

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
}