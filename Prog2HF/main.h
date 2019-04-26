#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef MEMTRACE
#include "memtrace.h"
#endif

#ifdef isSFML
#include <SFML/Graphics.hpp>
#endif

#include "schtring.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include "Compatibility.h"
#include "Parts.h"
#include "Inventory.h"
#include "atest.h"
#include "Builds.h"

enum enumMenu {
	eMain = 1,
	ePartsList = 11,
	ePartsAdd = 12,
	ePartsRemove = 13,
	eBuildsList = 21,
	eBuildsAdd = 22,
	eExit = 9
};

int main(int argc, char** argv);


void printMain();
void evaluateCommand(enum enumMenu&);
void printPartsList(Inventory&);
void saveParts(const Inventory&);
void saveOrders(const Orders&);
