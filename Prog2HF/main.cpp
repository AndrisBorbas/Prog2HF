// Copyright 2019 © Andris Borbás™, All Rights ¯\_(ツ)_/¯®. (ง ͠° ل͜ °)ง

#include "main.h"

//CompatibilityList IntelCompatList;

int main(int argc, char** argv)
{
	///Alapértelmezett parts fájl név
	char partsfilename[52] = "parts.txt";
	char ordersfilename[52] = "orders.txt";
	///Parts fájl nevének beállítása indítási parancsból
	if (argc > 1) strcpy(partsfilename, argv[1]);
	if (argc > 2) strcpy(ordersfilename, argv[2]);

	std::fstream partsFile;
	partsFile.open(partsfilename, std::ios_base::in | std::ios_base::out);
	std::fstream partsTempFile;
	partsTempFile.open("partstemp.txt", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

	std::fstream ordersFile;
	ordersFile.open(ordersfilename, std::ios_base::in | std::ios_base::out);
	std::fstream ordersTempFile;
	ordersTempFile.open("orderstemp.txt", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

	test1(partsFile, partsfilename);
	test1(partsTempFile, "partstemp.txt");
	test1(ordersFile, ordersfilename);
	test1(ordersTempFile, "orderstemp.txt");

	///első 5 sor átmásolása
	for (int i = 0; i < 5; i++){
		char temp[256];
		partsFile.getline(temp, 255);
		partsTempFile << temp << std::endl;
	}

	///pozíció mentése kiíráshoz
	std::streampos pos = partsTempFile.tellg();

	enumPart eP = eInvalid;
	enumMenu eM = eMain;
	TempInput tmp;
	Inventory inventory;
	Orders orders;

	while (partsFile >> tmp.instruction) {
#ifdef _DEBUG
		std::cout << tmp.instruction << std::endl;
#endif
		if (tmp.instruction[tmp.instruction.length() - 1] == ':') {
			setEnum(tmp.instruction, eP);
			if (eP != eInvalid) {
				inventory.loadPart(partsFile, tmp, eP);
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

	test3("wasd", "WAsd");

	String asd("wasdw");
	asd--;
	test4(asd, "wasd");

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

	//system("pause");

	animate('~');

	while (!(eM == eExit)) {
		switch (eM)
		{
		case eMain:
			printMain();
			break;
		case ePartsList:
			printPartsList(inventory);
			break;
		case ePartsAdd:
			addPartHelper(inventory, tmp);
			break;
		case ePartsRemove:
			removePartHelper(inventory, eM);
			break;
		case eBuildsList:
			clearcmd();
			break;
		case eBuildsAdd:
			clearcmd();
			break;
		case eExit:
			break;
		}
		evaluateCommand(eM);
	}

	saveInventory(partsTempFile, partsFile, inventory, pos, partsfilename);
	return 0;
}

void printMain() {
	clearcmd();
	std::cout << "11: Print all loaded parts \n12: Add new part \n13: Remove part \n\n21: Print a build \n22: Create new build \n\n9: Save&Exit\n";
}

void printPartsList(Inventory& inventory) {
	clearcmd();
	inventory.printInventory(std::cout);
	std::cout << "\n1: Return\n";
}

void addPartHelper(Inventory& inventory, TempInput& tmp) {
	clearcmd();
	std::cout << "1: CPU\n2: GPU\n3: MOBO\n4: RAM\n5: Case\n6: PSU\n7: SSD\n8: HDD\n\nPart type to add: ";
	std::cin >> tmp.instruction;
	//int a = tmp.instruction;
}

void removePartHelper(Inventory& inventory, enum enumMenu& eM) {
	clearcmd();
	inventory.printInventory(std::cout);
	std::cout << "\nType in the number of the part you want to remove (or 1 to return to menu): ";
	int a = evaluateInput(inventory);
	if (a == -1) {
		eM = eMain;
		return;
	}
	inventory.removePart(a);
	std::cout << "\nPart removed\n1: Return\n";
}

void saveInventory(std::fstream& tempFile, std::fstream& origFile, Inventory& inventory, std::streampos& pos, const char * partsfilename) {
	tempFile.clear();
	tempFile.seekp(pos, std::ios_base::beg);
	inventory.saveInventory(tempFile);
	origFile.close();
	tempFile.close();
	remove(partsfilename);
	rename("partstemp.txt", partsfilename);
}

void animate(char c) {
	std::cout << std::endl;
	for (int i = 0; i < 100; i++) {
		std::cout << c;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	std::cout << std::endl;
}

int evaluateInput(Inventory& inventory) {
	int a;
	while (std::cin >> a) {
		if (a == 1) return -1;
		if (a < 101) {
			std::cout << "\nNumber too small.\nTry again: ";
			continue;
		}
		if ((a - 101) > inventory.get_size()) {
			std::cout << "\nNumber too big.\nTry again: ";
			continue;
		}
		return a-101;
	}
}

void evaluateCommand(enum enumMenu& eM) {
	int cv;
	while (std::cin >> cv) {
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
