// Copyright 2019 © Andris Borbás™, All Rights ¯\_(ツ)_/¯®.

#include "main.h"

//CompatibilityList IntelCompatList;

int main(int argc, char** argv)
{
	///Default parts file name
	char partsfilename[52] = "parts.txt";
	///Set parts file name from command line
	if (argc > 1) strcpy(partsfilename, argv[1]);

	std::fstream partsFile;
	partsFile.open(partsfilename, std::ios::in | std::ios::out);

	test1(partsFile, partsfilename);

	//enumPart eP = eInvalid;
	enumMenu eM = eMain;
	TempInput tmp;
	/*
	Part** inv = new Part * [1];
	
	while (partsFile >> tmp.instruction) {
		std::cout << tmp.instruction << std::endl;
		if (tmp.instruction[tmp.instruction.length() - 1] == ':') {
			setEnum(tmp.instruction, eP);
			if (eP != eInvalid) {
				inv[0] = loadPart(partsFile, tmp, eP);
				std::cout << *(inv[0]);
			}
		}
	}
	dynamic_cast<CPU*>(inv[0])->burn();
	*/
	
	{
		Inventory inventory2;
		inventory2.push_back(new CPU("intel", "i3-4330", 800, 200, 2, "LGA1152", true));
		inventory2.push_back(new GPU("nvidia", "asd", 800, 2000, 4));
	}
	
	Inventory inventory;
	inventory.push_back(new CPU("intel", "i3-4330", 800, 200, 2, "LGA1152", true));
	inventory.push_back(new GPU("nvidia", "asd", 800, 2000, 4));

	test2(inventory);
	
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

	test3("wasd", "WAsd");

	String asd("wasdw");
	asd--;
	test4(asd, "wasd");


	Orders orders;

	/*
	partsFile.clear();
	std::streampos pos = partsFile.tellg();
	partsFile << std::endl << "CPU: \n";
	partsFile << i74790 << "\n";

	partsFile.flush();

	partsFile.seekg(pos);
	*/
	//inv[0] = loadPart(partsFile, tmp, eP);
	//partsFile << std::endl << "CPU: \n";
	//partsFile << *(inventory[0]);
	//std::cout << std::endl << *(inv[0]);

	while (!(eM == eExit)) {
		switch (eM)
		{
		case eMain:
			print();
			break;
		case ePartsList:
			printPartsList(inventory);
			//ez azért van hogy végigfusson input nélkül is
			return 0;
			break;
		case ePartsAdd:
			system("cls");
			break;
		case ePartsRemove:
			system("cls");
			break;
		case eBuildsList:
			system("cls");
			break;
		case eBuildsAdd:
			system("cls");
			break;
		case eExit:
			return 0;
		}
		evaluateCommand(eM);
	}
}

void print() {
	system("cls");
	std::cout << "11: Print all loaded parts \n12: Add new part \n13: Remove part \n\n21: Print a build \n22: Create new build \n\n9: Save&Exit\n";
}

void printPartsList(Inventory& inventory) {
	system("cls");
	for (int i = 0; i < inventory.get_size(); i++) {
		std::cout << i + 1 << ": " << *(inventory[i]) << std::endl;
	}
	std::cout << "\n1: Return";
}

void evaluateCommand(enum enumMenu& eM) {
	char c[52];
	std::stringstream v;
	int cv;
	while (std::cin >> c) {
		std::stringstream().swap(v);
		v << c;
		v >> cv;
		switch (cv) {
		case 1:
			eM = eMain;
			return;
		case 11:
			eM = ePartsList;
			return;
		case 12:
			eM = ePartsAdd;
			return;
		case 13:
			eM = ePartsRemove;
			return;
		case 21:
			eM = eBuildsList;
			return;
		case 22:
			eM = eBuildsAdd;
			return;
		case 9:
			eM = eExit;
			return;
		case 0:
			break;
		}
		std::cout << "Invalid command: " << cv;
	}
}
