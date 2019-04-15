#include "Compatibility.h"

CompatibilityList::CompatibilityList(String & slist) :size(0), capacity(slist.size() / 4) {
	list = new String[capacity];
#ifdef _DEBUG
	std::cout << "Compatibility List constructed with members : " << std::endl<<"    ";
#endif
	String temp = "";
	size_t j = 0;
	for (int i = 0; i < slist.size(); i++) {
		if (capacity <= j) {
			String * temp = list;
			size_t oldsize = capacity;
			capacity *= 2;
			list = new String[capacity];
			for (size_t i = 0; i < oldsize; i++) {
				*(list + i) = *(temp + i);
			}
			delete[] temp;
		}
		if (slist[i] == ',' || slist[i] == ';') {
			*(list + j) = temp;
			temp = "";
#ifdef _DEBUG
			std::cout << *(list + j) << ", ";
#endif
			j++;
		}
		else {
			temp += slist[i];
		}
	}
	size = j;
#ifdef _DEBUG
	std::cout << std::endl;
#endif
}

void CompatibilityList::addItems(String & slist) {
	String temp = "";
	size_t j = size;
#ifdef _DEBUG
	std::cout << "Compatibility List expanded with members : " << std::endl << "    ";
#endif
	for (int i = 0; i < slist.size(); i++) {
		if (capacity <= j) {
			String * temp = list;
			size_t oldsize = capacity;
			capacity *= 2;
			list = new String[capacity];
			for (size_t i = 0; i < oldsize; i++) {
				*(list + i) = *(temp + i);
			}
			delete[] temp;
		}
		if (slist[i] == ',' || slist[i] == ';') {
			*(list + j) = temp;
			temp = "";
#ifdef _DEBUG
			std::cout << *(list + j) << ", ";
#endif
			j++;
		}
		else {
			temp += slist[i];
		}
	}
	size = j;
#ifdef _DEBUG
	std::cout << std::endl;
#endif
}

std::ostream& operator<<(std::ostream& os, const CompatibilityList& cl) {
	for (int i = 0; i < cl.get_length(); i++) {
		os << *(cl.get_listp() + i) << ", ";
	}
	os << std::endl;
	return os;
}