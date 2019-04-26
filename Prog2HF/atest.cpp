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
#ifdef _DEBUG
	std::cout << "Test 1 Succesful\n";
#endif
}

bool test2(Inventory & inventory) {
	if (nullptr == (dynamic_cast<CPU*>(inventory[0]))) {
		std::cerr << "The first item wasnt a CPU";
		return false;
	}
	if (nullptr == (dynamic_cast<GPU*>(inventory[1]))) {
		std::cerr << "The first item wasnt a CPU";
		return false;
	}
	if (!(nullptr == (dynamic_cast<GPU*>(inventory[0])))) {
		std::cerr << "The first item was a GPU instead of a CPU";
		return false;
	}
	if (!(nullptr == (dynamic_cast<CPU*>(inventory[1])))) {
		std::cerr << "The first item was a CPU instead of a GPU";
		return false;
	}
#ifdef _DEBUG
	std::cout << "Test 2 Succesful\n";
#endif
	return true;
}

bool test3(String test1, String test2) {
	bool temp = (test1 == test2);
	if (!temp) {
		std::cerr << "Result does not equal the expected result";
	}
#ifdef _DEBUG
	std::cout << "Test 3 Succesful\n";
#endif
	return temp;
}

bool test4(String asd, const char* test) {
	bool temp = (asd == test);
	if (!temp) {
		std::cerr << "Result does not equal the expected result";
	}
#ifdef _DEBUG
	std::cout << "Test 4 Succesful\n";
#endif
	return temp;
}
