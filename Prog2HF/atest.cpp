#include "atest.h"

void test1(std::fstream& partsFile, const char filename[52]) {
	if (!partsFile) {
		std::cerr << "Could not open file: " << filename << "\nTrying to create it. \n\n";
		partsFile.open(filename, std::ios::out | std::ios::trunc | std::ios::in);
		if (!partsFile) {
			std::cerr << "Could not create file: " << filename;
			std::cerr << "\n\nExiting because the program cannot run without the file.";
			exit(EXIT_FAILURE);
		}
	}
#ifdef _DEBUG
	std::cout << "Filestream test Succesful\n";
#endif
}

bool test3(String test1, String test2) {
	bool temp = (test1 == test2);
	if (!temp) {
		std::cerr << "Result does not equal the expected result";
	}
#ifdef _DEBUG
	std::cout << "String case unsensitive comparison test Succesful\n";
#endif
	return temp;
}

bool test4(String asd, const char* test) {
	bool temp = (asd == test);
	if (!temp) {
		std::cerr << "Result does not equal the expected result";
	}
#ifdef _DEBUG
	std::cout << "String last character removal Succesful\n";
#endif
	return temp;
}

bool test5(String asd, const char* test) {
	bool temp = (asd == test);
	if (!temp) {
		std::cerr << "Result does not equal the expected result";
	}
#ifdef _DEBUG
	std::cout << "String first x character removal Succesful\n";
#endif
	return temp;
}