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
	for (int i = 0; i < 6; i++) {
		char temp[256];
		partsFile.getline(temp, 255);
		partsTempFile << temp << std::endl;
	}
	for (int i = 0; i < 6; i++) {
		char temp[256];
		ordersFile.getline(temp, 255);
		ordersTempFile << temp << std::endl;
	}

	///pozíció mentése kiíráshoz
	std::streampos partsPos = partsTempFile.tellg();
	///pozíció mentése kiíráshoz
	std::streampos ordersPos = ordersTempFile.tellg();

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

	while (ordersFile >> tmp.instruction) {
#ifdef _DEBUG
		std::cout << tmp.instruction << std::endl;
#endif
		if (tmp.instruction[tmp.instruction.length() - 1] == ':') {
			orders.load(ordersFile, inventory, tmp);
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

#if defined(_DEBUG) || defined(NDEBUG)
	animate();
#endif

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
			if (-1 == addPartHelper(inventory, tmp, eP)) {
				eM = eMain;
				continue;
			}
			break;
		case ePartsRemove:
			removePartHelper(inventory);
			eM = eMain;
			continue;
		case eBuildsList:
			printOrdersList(orders);
			break;
		case eBuildsAdd:
			addBuildHelper(orders, inventory);
			eM = eMain;
			continue;
		case eBuildsComplete:
			completeOrderHelper(orders);
			eM = eMain;
			continue;
		case eBuildsRemove:
			removeOrderHelper(orders);
			eM = eMain;
			continue;
			break;
		case eExit:
			break;
		}
		if (eM == ePartsAdd)eM = eMain;
		evaluateCommand(eM);
	}

	save(partsTempFile, partsFile, inventory, partsPos, partsfilename, "partstemp.tmp");
	save(ordersTempFile, ordersFile, orders, ordersPos, ordersfilename, "orderstemp.tmp");
	return 0;
}

void printMain() {
	clearcmd();
	std::cout << "11: Print all loaded parts \n12: Add new part \n13: Remove part \n\n21: Print all orders \n22: Create new order \n23: Mark order as completed \n24: Remove order \n\n9: Save&Exit\n";
}

void printPartsList(Inventory& inventory) {
	clearcmd();
	inventory.print(std::cout);
	std::cout << "\n1: Return\n";
}

void printOrdersList(Orders& orders) {
	clearcmd();
	std::cout << orders;
	std::cout << "\n1: Return\n";
}

int addPartHelper(Inventory& inventory, TempInput& tmp, enum enumPart& eP) {
	clearcmd();
	std::cout << "Type in the number of the type of part you want to add (or 1 to return to menu): \n";
	std::cout << "101: CPU\n102: GPU\n103: Motherboard\n104: RAM\n105: Case\n106: PSU\n107: SSD\n108: HDD\n\n";
	int a;
	std::cin >> a;
	if (a == 1)return -1;
	clearcmd();
	a -= 100;
	setEnumfromInt(a, eP);
	if (eP != eInvalid) {
		inventory.loadPart(std::cin, tmp, eP);
		std::cout << "1: Return\n";
	}
	return 0;
}

void removePartHelper(Inventory& inventory) {
	clearcmd();
	while (true) {
		inventory.print(std::cout);
		std::cout << "\nType in the number of the part you want to remove (or 1 to return to menu): ";
		int a = evaluateInput(inventory);
		if (a == -1) {
			return;
		}
		inventory.remove(a);
		clearcmd();
		std::cout << "Part removed\n\n";
	}
	return;
}

void addBuildHelper(Orders& orders, Inventory& inventory) {
	clearcmd();
	Build* temp = new Build;
	temp->push_back(inventory[partSelector(inventory, "CPU")]);
	temp->push_back(inventory[partSelector(inventory, "Graphics Card")]);
	temp->push_back(inventory[partSelector(inventory, "Motherboard")]);
	temp->push_back(inventory[partSelector(inventory, "RAM")]);
	temp->push_back(inventory[partSelector(inventory, "Case")]);
	temp->push_back(inventory[partSelector(inventory, "Powersupply")]);
	bool once = true;
	while (true) {
		std::cout << "Select storage: \n\n";
		inventory.print(std::cout, "SSD");
		inventory.print(std::cout, "HDD");
		int a;
		std::cin >> a;
		a -= 101;
		clearcmd();
		std::cout << "Selected: " << simple << *(inventory[a]) << "\n\n";
		temp->push_back(inventory[a]);
		if (once) {
			orders.push_back(temp);
			once = false;
		}
		std::cout << "Order Registered:\n";
		std::cout << *(orders[orders.get_size() - 1]);

		std::cout << "\n2: Add more storage\n1 : Return\n";
		std::cin >> a;
		clearcmd();
		if (a == 1 || a == 9)return;
	}
	return;
}

int partSelector(Inventory& inventory, const char* type) {
	std::cout << "Select a " << type << ": \n\n";
	inventory.print(std::cout, type);
	std::cout << std::endl;
	int a;
	std::cin >> a;
	a -= 101;
	clearcmd();
	std::cout << "Selected: " << simple << *(inventory[a]) << "\n\n";
	return a;
}

void completeOrderHelper(Orders& orders) {
	clearcmd();
	while (true) {
		std::cout << simple << orders;
		std::cout << "\nType in the number of the order you want to mark as completed (or 1 to return to menu): ";
		int a = evaluateInput(orders);
		if (a == -1)return;
		clearcmd();
		orders.complete(a);
	}
}

void removeOrderHelper(Orders& orders) {
	clearcmd();
	while (true) {
		std::cout << simple << orders;
		std::cout << "\nType in the number of the order you want to remove (or 1 to return to menu): ";
		int a = evaluateInput(orders);
		if (a == -1) {
			return;
		}
		orders.remove(a);
		clearcmd();
		std::cout << "Order removed\n\n";
	}
}

template <typename T>
void save(std::fstream& tempFile, std::fstream& origFile, T& classwithsavefunc, std::streampos& pos, const char* filename, const char* tempfilename) {
	tempFile.clear();
	tempFile.seekp(pos, std::ios_base::beg);
	classwithsavefunc.save(tempFile);
	origFile.close();
	tempFile.close();
	remove(filename);
	rename(tempfilename, filename);
}

void animate(char c) {
	std::cout << std::endl;
	for (int i = 0; i < 100; i++) {
		std::cout << c;
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
	std::cout << std::endl << "\n\t\t\t\tFully loaded\n\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(999));
}

template <typename T>
int evaluateInput(T& classwithsize) {
	int idx;
	while (std::cin >> idx) {
		if (idx == 1) return -1;
		if (idx < 101) {
			std::cout << "\nNumber too small.\nTry again: ";
			continue;
		}
		if ((idx - 101) > classwithsize.get_size()) {
			std::cout << "\nNumber too big.\nTry again: ";
			continue;
		}
		return idx - 101;
	}
	return -1;
}

void evaluateCommand(enum enumMenu& eM) {
	int cv;
	while (!std::cin.eof()) {
		std::cin >> cv;
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
		case 23:
			eM = eBuildsComplete;
			return;
		case 24:
			eM = eBuildsRemove;
			return;
		case 9:
			eM = eExit;
			return;
		case 0:
			break;
		}
		std::cout << "Invalid command: " << cv << "\nTry again: ";
	}
	eM = eExit;
	return;
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