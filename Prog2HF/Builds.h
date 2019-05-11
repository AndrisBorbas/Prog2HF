#pragma once

#include "Inventory.h"

///Egy gépkonfigot tárol
class Build {
	///alkatrészek
	Part** components; 	///max méret
	size_t capacity;	///méret
	int size;			///ár
	int price;
public:
	Build(size_t capacity = 7) :capacity(capacity), size(0), price(0) {
		components = new Part * [capacity];
	}
	~Build() {
		delete[] components;
	}

	///végére beszúrás
	template<typename T>
	void push_back(T* part) {
		if (size == (int)capacity) {
			capacity += 4;
			Part** temp = new Part * [capacity];
			for (int i = 0; i < size; i++) {
				temp[i] = components[i];
			}
			delete[] components;
			components = temp;
		}
		components[size] = part;
		price += (*part).get_price();
		size++;
	}
	int get_price() { return price; }
	///konfig kiírása
	void print(std::ostream& os) const;
	///konfig betöltése
	void load(std::fstream& is, Inventory& inventory, TempInput& tmp);
	///konfig mentése
	void save(std::ostream& os) const;

	const Part* operator[](int idx) const {
		return components[idx];
	}
	Part* operator[](int idx) {
		return components[idx];
	}
};

std::ostream& operator<<(std::ostream& os, const Build& b);


///A megrendelt konfigokat tárolja
class Orders {
	///konfigok
	Build** builds;		///teljesített
	bool* completed;	///max méret
	size_t capacity;	///méret
	int size;
public:
	Orders(size_t capacity = 1) :capacity(capacity), size(0) {
		builds = new Build * [capacity];
		completed = new bool[capacity] {false};
	}
	~Orders() {
		for (int i = 0; i < size; i++) {
			delete builds[i];
		}
		delete[] builds;
		delete[] completed;
	}

	int get_size() {
		return size;
	}

	///végére beszúrás
	void push_back(Build* build) {
		if (size == (int)capacity) {
			capacity *= 2;
			Build** temp = new Build * [capacity];
			for (int i = 0; i < size; i++) {
				temp[i] = builds[i];
			}
			delete[] builds;
			builds = temp;

			bool* btemp = new bool[capacity];
			for (int i = 0; i < size; i++) {
				btemp[i] = completed[i];
			}
			delete[] completed;
			completed = btemp;
		}
		builds[size] = build;
		completed[size] = false;
		size++;
	}

	///megrendelések betöltése
	void load(std::fstream& is, Inventory& inventory, TempInput& tmp);
	///megrendelések mentése
	void save(std::ostream& os) const;
	///megrendelés teljesített állapotba tétele
	void complete(int idx);
	///megrendelés törlése
	void remove(int idx);

	void print(std::ostream& os) const;
	void print(simple_ostream& tos) const;

	const Build* operator[](int idx) const {
		return builds[idx];
	}
	Build* operator[](int idx) {
		return builds[idx];
	}

};

std::ostream& operator<<(std::ostream& os, const Orders& o);
std::ostream& operator<<(simple_ostream tos, const Orders& o);
