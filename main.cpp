#include "variables.h"

std::vector<std::string> positiveNewsEvents, negativeNewsEvents;				// Vectors of positive/negative events
std::string fileOutput = "";													// Used for getline() operations
stocks EggCorp("EggCorp", 50, 0.1, 10);											// Companies' objects of stocks class
stocks OrangeLTD("OrangeLTD", 500, 10, 0);

int main() {
	srand((unsigned)time(NULL));												// Generate random seed
	std::ifstream positiveEvents("positive-news-events.txt");					// Open news events' files
	std::ifstream negativeEvents("negative-news-events.txt");

	while (getline(positiveEvents, fileOutput)) {								// Read in from news events' files to vectors
		positiveNewsEvents.push_back(fileOutput);
	}
	while (getline(negativeEvents, fileOutput)) {
		negativeNewsEvents.push_back(fileOutput);
	}
}