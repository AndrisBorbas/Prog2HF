#pragma once

#include "Parts.h"

enum enumPart {
	eInvalid = 0,
	eCPU = 1,
	eGPU = 2,
	eMOBO = 3,
	eRAM = 4,
	eCase = 5,
	ePSU = 6,
	eSSD = 7,
	eHDD = 8
};

class Inventory {
	Part** stock;
	size_t capacity;
	unsigned int size;
public:
	Inventory(size_t capacity = 1) :capacity(capacity), size(0) {
		stock = new Part * [capacity];
	}
	~Inventory() {
		for (size_t i = 0; i < size; i++) {
			delete stock[i];
		}
		delete[] stock;
	}

	int get_size() {
		return size;
	}

	void loadPart(std::istream& is, TempInput& tmp, enum enumPart);

	template<typename T>
	void push_back(T* part) {
		if (size == capacity) {
			capacity *= 2;
			Part** temp = new Part * [capacity];
			for (size_t i = 0; i < size; i++) {
				temp[i] = stock[i];
			}
			delete[] stock;
			stock = temp;
		}
		stock[size] = part;
		size++;
	}

	const Part* operator[](int idx) const {
		return stock[idx];
	}
	Part* operator[](int idx) {
		return stock[idx];
	}
};

void setEnum(String inst, enum enumPart&);

void LoadParams(std::istream& is, TempInput& tmp, int const params);