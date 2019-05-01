#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <chrono>
#include <thread>

#ifdef MEMTRACE
#include "memtrace.h"
#endif

#ifdef isSFML
#include <SFML/Graphics.hpp>
#endif

#include "schtring.h"
#include <iostream>
#include <fstream>
#include <typeinfo>
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

void animate(char);
void printMain();
void evaluateCommand(enum enumMenu&);
void printPartsList(Inventory&);
void addPartHelper(Inventory&, TempInput&);
void saveParts(const Inventory&);
void saveOrders(const Orders&);

inline void clearcmd() {
#ifdef _MSC_VER
	system("cls");
#endif
#ifndef _MSC_VER
	system("clear");
#endif 
}