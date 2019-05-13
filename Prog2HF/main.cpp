// Copyright 2019 © Andris Borbás™, All Rights ¯\_(ツ)_/¯®. (ง ͠° ل͜ °)ง

#include "main.h"

#if defined(MEMTRACE) || defined(DMEMTRACE)
#include "memtrace.h"
#endif

//CompatibilityList IntelCompatList;

int main(int argc, char** argv)
{
	///Alapértelmezett fájl nevek
	char partsfilename[52] = "parts.txt";
	char ordersfilename[52] = "orders.txt";
	///fájl nevek beállítása indítási parancsból
	if (argc > 1) strcpy(partsfilename, argv[1]);
	if (argc > 2) strcpy(ordersfilename, argv[2]);

	///Alkatrészek
	std::fstream partsFile;
	partsFile.open(partsfilename, std::ios_base::in | std::ios_base::out);
	std::fstream partsTempFile;
	partsTempFile.open("partstemp.tmp", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

	///Megrendelések
	std::fstream ordersFile;
	ordersFile.open(ordersfilename, std::ios_base::in | std::ios_base::out);
	std::fstream ordersTempFile;
	ordersTempFile.open("orderstemp.tmp", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

	test1(partsFile, partsfilename);
	test1(partsTempFile, "partstemp.tmp");
	test1(ordersFile, ordersfilename);
	test1(ordersTempFile, "orderstemp.tmp");

	///első 6 sor átmásolása
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
	std::streampos ordersPos = ordersTempFile.tellg();

	///Alkatrész típusa betöltéshez
	enumPart eP = eInvalid;
	///Menüpontok közti váltás
	enumMenu eM = eMain;
	///
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

	///megrendelések betöltése fájlból
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

	///main menu loop
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

	///mentés
	save(partsTempFile, partsFile, inventory, partsPos, partsfilename, "partstemp.tmp");
	save(ordersTempFile, ordersFile, orders, ordersPos, ordersfilename, "orderstemp.tmp");
	return 0;
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