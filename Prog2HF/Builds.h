#pragma once

#include "Inventory.h"

///Egy gépkonfigot tárol
class Build {
	Part** components;
	size_t capacity;
	int size;
	int price;
public:
	Build(size_t capacity = 7) :capacity(capacity), size(0), price(0) {
		components = new Part * [capacity];
	}
	~Build() {
		delete[] components;
	}

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

	void print(std::ostream& os) const;

	void load(std::fstream& is, Inventory& inventory, TempInput& tmp);

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
	Build** builds;
	bool* completed;
	size_t capacity;
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

	void load(std::fstream& is, Inventory& inventory, TempInput& tmp);

	void save(std::ostream& os) const;

	void complete(int idx);

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
