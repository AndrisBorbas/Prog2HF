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
	partsTempFile.open("partstemp.tmp", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

	std::fstream ordersFile;
	ordersFile.open(ordersfilename, std::ios_base::in | std::ios_base::out);
	std::fstream ordersTempFile;
	ordersTempFile.open("orderstemp.tmp", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

	test1(partsFile, partsfilename);
	test1(partsTempFile, "partstemp.tmp");
	test1(ordersFile, ordersfilename);
	test1(ordersTempFile, "orderstemp.tmp");

	///első 5 sor átmásolása
	for (int i = 0; i < 5; i++) {
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

	///alkatrészek betöltése fájlból
	while (partsFile >> tmp.instruction) {
#ifdef _DEBUG
		std::cout << tmp.instruction << std::endl;
#endif
		if (tmp.instruction[tmp.instruction.length() - 1] == ':') {
			setEnumfromString(tmp.instruction, eP);
			if (eP != eInvalid) {
				inventory.loadPart(partsFile, tmp, eP);
			}
		}
	}


	/*
	String slist = "1,2,3,4,5,6,7,8,9;";
	CompatibilityList intellist(slist);
	IntelCompatList.addItems(slist);
	std::cout << std::boolalpha << (intellist == "10") << (intellist == "2");
	*/
	//CPU i74790("intel", "i3-4330", 800, 200, 2, "LGA1152", true);

	test3("wasd", "WAsd");
	{
		String asd("wasdw");
		asd--;
		test4(asd, "wasd");
	}
	{
		String asd("class CPU");
		asd.removeFirstX(6);
		test5(asd, "CPU");
	}

	//system("pause");

	animate();

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
			addPartHelper(inventory, tmp, eP);
			break;
		case ePartsRemove:
			if (-1 == removePartHelper(inventory)) {
				eM = eMain;
				continue;
			}
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
		if (eM == ePartsAdd)eM = eMain;
		evaluateCommand(eM);
	}

	save(partsTempFile, partsFile, inventory, pos, partsfilename, "partstemp.tmp");
	return 0;
}

void printMain() {
	clearcmd();
	std::cout << "11: Print all loaded parts \n12: Add new part \n13: Remove part \n\n21: Print a build \n22: Create new build \n\n9: Save&Exit\n";
}

void printPartsList(Inventory& inventory) {
	clearcmd();
	inventory.print(std::cout);
	std::cout << "\n1: Return\n";
}

void addPartHelper(Inventory& inventory, TempInput& tmp, enum enumPart& eP) {
	clearcmd();
	std::cout << "Type in the number of the type of part you want to add (or 1 to return to menu): \n";
	std::cout << "101: CPU\n102: GPU\n103: Motherboard\n104: RAM\n105: Case\n106: PSU\n107: SSD\n108: HDD\n\n";
	int a;
	std::cin >> a;
	if (a == 1)return;
	clearcmd();
	a -= 100;
	setEnumfromInt(a, eP);
	if (eP != eInvalid) {
		inventory.loadPart(std::cin, tmp, eP);
		std::cout << "1: Return\n";
	}
}

int removePartHelper(Inventory& inventory) {
	clearcmd();
	while (true) {
		inventory.print(std::cout);
		std::cout << "\nType in the number of the part you want to remove (or 1 to return to menu): ";
		int a = evaluateInput(inventory);
		if (a == -1) {
			return -1;
		}
		inventory.removePart(a);
		clearcmd();
		std::cout << "Part removed\n\n";
	}
	return 0;
}

void save(std::fstream& tempFile, std::fstream& origFile, Inventory& inventory, std::streampos& pos, const char* filename, const char* tempfilename) {
	tempFile.clear();
	tempFile.seekp(pos, std::ios_base::beg);
	inventory.save(tempFile);
	origFile.close();
	tempFile.close();
	remove(filename);
	rename(tempfilename, filename);
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
		return a - 101;
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
		std::cout << "Invalid command: " << cv << "\nTry again: ";
	}
}

void setEnumfromInt(int a, enumPart& eP) {
	switch (a)
	{
	case 1:
		eP = eCPU;
		break;
	case 2:
		eP = eGPU;
		break;
	case 3:
		eP = eMOBO;
		break;
	case 4:
		eP = eRAM;
		break;
	case 5:
		eP = eCase;
		break;
	case 6:
		eP = ePSU;
		break;
	case 7:
		eP = eSSD;
		break;
	case 8:
		eP = eHDD;
		break;
	default:
		break;
	}
}