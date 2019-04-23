#pragma once

#include "main.h"

class Inventory {
	Part** stock;
	size_t capacity;
	int size;
public:
	Inventory(size_t capacity = 1) :capacity(capacity), size(0) {
		stock = new Part * [capacity];
	}
	~Inventory() {
		delete[] stock;
	}

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

Part* loadPart(std::istream& is, TempInput& tmp, enum enumPart);

void setEnum(String inst, enum enumPart&);

void LoadParams(std::istream& is, TempInput& tmp, int const params);