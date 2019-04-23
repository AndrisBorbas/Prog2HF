#include "atest.h"

void test1(std::fstream& partsFile, char partsfilename[52]) {
	if (!partsFile) {
		std::cerr << "Could not open parts file: " << partsfilename << "\nTrying to create it. \n\n";
		partsFile.open(partsfilename, std::ios::out | std::ios::trunc | std::ios::in);
		if (!partsFile) {
			std::cerr << "Could not create parts file: " << partsfilename;
			std::cerr << "\n\nExiting because the program cannot run without a parts file.";
			exit(EXIT_FAILURE);
		}
	}
}
