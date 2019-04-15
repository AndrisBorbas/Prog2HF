#pragma once

#include <iostream>
#include "schtring.h"

class CompatibilityList {
	size_t capacity;
	int size;
	String* list;
public:
	explicit CompatibilityList() :size(0), capacity(1) { list = new String[capacity]; }
	explicit CompatibilityList(String &);

	~CompatibilityList() { delete[] list; }

	int get_length() const { return size; }

	String* get_listp() const { return list; }

	void addItems(String &);

	bool operator==(String & rhs) {
		for (int i = 0; i < size; i++) {
			if (*(list + i) == rhs) {
				return true;
			}
		}
		return false;
	}

	bool operator==(const char * rhs) {
		for (int i = 0; i < size; i++) {
			if (*(list + i) == rhs) {
				return true;
			}
		}
		return false;
	}
};

std::ostream& operator<<(std::ostream& os, const CompatibilityList& cl);

template <typename T1 = String, typename T2 = String>
bool compatible(T1 is, T2 with, CompatibilityList cl) {
	/*
	switch (is) {
	default:
		throw std::logic_error("incompatible");
	case "Intel":
	case "intel":
		if (true) {
			throw "erroe";
		}
	}
	*/

}