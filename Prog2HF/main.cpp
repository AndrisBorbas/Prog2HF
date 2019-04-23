// Copyright 2019 © Andris Borbás™, All Rights ¯\_(ツ)_/¯®.

#ifdef isSFML
#include <SFML/Graphics.hpp>
#endif
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "main.h"

CompatibilityList IntelCompatList;

int main(int argc, char** argv)
{
	std::cout << "hi" << std::endl;

	///Default parts file name
	char partsfilename[52] = "parts.txt";
	///Set parts file name from command line
	if (argc > 1) strcpy(partsfilename, argv[1]);

	std::fstream partsFile;
	partsFile.open(partsfilename, std::ios::in | std::ios::out);
	if (!partsFile) {
		std::cout << "Could not open parts file: " << partsfilename << "\nTrying to create it. \n\n";
		partsFile.open(partsfilename, std::ios::out | std::ios::trunc | std::ios::in);
		if (!partsFile) {
			std::cout << "Could not create parts file: " << partsfilename;
			partsFile.open(partsfilename, std::ios::out | std::ios::trunc | std::ios::in);
			throw std::logic_error("Couldn't read/create parts file");
		}
	}

	enumPart e = eInvalid;
	TempInput tmp;
	Part** inventory = new Part * [1];

	while (partsFile >> tmp.instruction) {
		std::cout << tmp.instruction << std::endl;
		if (tmp.instruction[tmp.instruction.length() - 1] == ':') {
			setEnum(tmp.instruction, e);
			if (e != eInvalid) {
				inventory[0] = loadPart(partsFile, tmp, e);
				std::cout << *(inventory[0]);
			}
		}
	}
	/*
	std::cout << "hi" << std::endl;
	String a = "1";
	String b = "2";
	String c = a;
	String slist = "1,2,3,4,5,6,7,8,9;";
	CompatibilityList intellist(slist);
	IntelCompatList.addItems(slist);
	std::cout << std::boolalpha << (intellist == "10") << (intellist == "2");
	*/
	CPU i74790("intel", "i3-4330", 800, 200, 2, "LGA1152", true);
	//Part part("brand", "type", 1);

	//std::cout << part << std::endl << i74790;
	/*
	String asd("wasd,");
	asd--;
	std::cout << asd;
	*/
	//std::streampos pos = partsFile.tellg();
	/*
	partsFile.seekp(1);
	partsFile.seekg(1);*/
	partsFile.clear();
	std::streampos pos = partsFile.tellg();
	partsFile << std::endl << "CPU: \n";
	partsFile << i74790 << "\n";

	partsFile.flush();
	//partsFile.clear();

	partsFile.seekg(pos);

	inventory[0] = loadPart(partsFile, tmp, e);
	//partsFile << std::endl << "CPU: \n";
	//partsFile << *(inventory[0]);
	std::cout << std::endl << *(inventory[0]);
}