#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS		//disable printf unsecure error
#pragma warning(disable : 4996)		//disable strlwr deprecated error
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#endif

#include <chrono>
#include <thread>

#ifdef MEMTRACE
#include "memtrace.h"
#endif

#ifdef isSFML
#include <SFML/Graphics.hpp>
#endif

#include "schtring.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <limits>
#include "Parts.h"
#include "Inventory.h"
#include "Builds.h"

///menü almenüi
enum enumMenu {
	eMain = 1,
	ePartsList = 11,
	ePartsAdd = 12,
	ePartsRemove = 13,
	eBuildsList = 21,
	eBuildsAdd = 22,
	eBuildsComplete = 23,
	eBuildsRemove = 24,
	eExit = 9
};

///kiírja a megrendeléseket
void printOrdersList(Orders& orders);

///csinál egy sor animációt
void animate(char c = '~');

///kiírja a főmenüt
void printMain();

///bemenet alapján vált a menük között
void evaluateCommand(enum enumMenu&);

///kiírja az összes betölttött alkatrészt
void printPartsList(Inventory&);

///beállítja a part loadert
void setEnumfromInt(int a, enumPart& eP);

///új alkatrészt tölt be console inputról
int addPartHelper(Inventory&, TempInput&, enumPart&);

///törli a kiválasztott alkatrészt
void removePartHelper(Inventory&);

///egy configot lehet csinálni vele
void addBuildHelper(Orders& orders, Inventory& inventory);

///konfighoz választ alkatrészt
int partSelector(Inventory& inventory, const char* type);

///megrendelést lehet teljesítetté tenni
void completeOrderHelper(Orders& orders);

///megrendelést lehet vele törölni
void removeOrderHelper(Orders& orders);

///átalakítja a beírt számot indexelővé
template <typename T>
int evaluateInput(T&);

///n edik sorra ugrik egy file streamben
inline std::fstream& GotoLine(std::fstream& file, unsigned int n) {
	file.seekg(std::ios::beg);
	for (unsigned int i = 0; i < n - 1; ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

///kitörli a terminált
inline void clearcmd() {
#ifdef _MSC_VER
	system("cls");
#endif
#ifndef _MSC_VER
	system("clear");
#endif 
}