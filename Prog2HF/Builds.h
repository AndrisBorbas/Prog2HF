#pragma once

#include "Parts.h"

///Egy gépkonfigot tárol
class Build {
	Part** components;
	int* count;
	size_t capacity;
	unsigned int size;
public:
	Build(size_t capacity = 7) :capacity(capacity), size(0) {
		components = new Part * [capacity];
		count = new int[capacity];
	}
	~Build() {
		for (size_t i = 0; i < size; i++) {
			delete components[i];
		}
		delete[] components;
		delete[] count;
	}

	template<typename T>
	void push_back(T* part);

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
	Build* builds;
	bool* completed;
	size_t capacity;
	unsigned int size;
public:
	Orders(size_t capacity = 1) :capacity(capacity), size(0) {
		builds = new Build[capacity];
		completed = new bool[capacity] {false};
	}
	~Orders() {
		delete[] builds;
		delete[] completed;
	}

	template<typename T>
	void push_back(T* part);

	const Build operator[](int idx) const {
		return builds[idx];
	}
	Build operator[](int idx) {
		return builds[idx];
	}

};

std::ostream& operator<<(std::ostream& os, const Orders& o);