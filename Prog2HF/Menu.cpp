#include "Menu.h"

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
		while (true) {
			a = evaluateInput(inventory);
			if (inventory.findbyIndex(a) == "SSD" || inventory.findbyIndex(a) == "HDD") break;
			std::cout << "\nEntered part doesn't match the requirements.\nTry again: ";
		}
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
	while (true) {
		a = evaluateInput(inventory);
		if (inventory.findbyIndex(a) == type) break;
		std::cout << "\nEntered part doesn't match the requirements.\nTry again: ";
	}
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