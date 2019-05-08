#pragma once

#include "Parts.h"
#include <fstream>

///Alkatrész tároló
class Inventory {
	///Raktár
	Part** stock;		///kapacitás
	size_t capacity;	///méret
	int size;			///milyen típusú alkatrész
	String* type;
public:
	Inventory(size_t capacity = 1) :capacity(capacity), size(0) {
		stock = new Part * [capacity];
		type = new String[capacity];
	}
	~Inventory() {
		for (int i = 0; i < size; i++) {
			delete stock[i];
		}
		delete[] stock;
		delete[] type;
	}

	int get_size() {
		return size;
	}

	String get_type(int i) {
		return *(type + i);
	}

	///Betölt egy alkatrészt fájlból
	void loadPart(std::fstream& is, TempInput& tmp, enumPart);
	///Betölt egy alkatrészt terminalból
	void loadPart(std::istream& is, TempInput& tmp, enumPart);

	///Raktár mentése egy streamre
	void save(std::ostream& os);

	///Raktár kiírása egy streamre
	void print(std::ostream& os, const String& test = "-1");

	///Egy alkatrész kitörlése a raktárból
	void remove(int idx);

	///Megkeres egy alkatrészt a típusa alapján és visszaadja az indexét
	int findbyType(const String& s0) const;

	///Egy alkatrész hozzáadása a raktárhoz
	template<typename T>
	void push_back(T* part, String type);

	const Part* operator[](int idx) const {
		return stock[idx];
	}
	Part* operator[](int idx) {
		return stock[idx];
	}
};

///Jelölőkk alapján betölti az alkatrész paramétereit
void loadParams(std::fstream& is, TempInput& tmp, int const params);

void loadBaseParams(std::istream& is, TempInput& tmp);

void loadCPUParams(std::istream& is, TempInput& tmp);

void loadGPUParams(std::istream& is, TempInput& tmp);

void loadMOBOParams(std::istream& is, TempInput& tmp);

void loadRAMParams(std::istream& is, TempInput& tmp);

void loadCaseParams(std::istream& is, TempInput& tmp);

void loadPSUParams(std::istream& is, TempInput& tmp);

void loadSSDParams(std::istream& is, TempInput& tmp);

void loadHDDParams(std::istream& is, TempInput& tmp);