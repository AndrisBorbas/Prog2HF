#include "Builds.h"

template<typename T>
void Build::push_back(T* part) {
	if (size == capacity) {
		capacity += 4;
		Part** temp = new Part * [capacity];
		for (size_t i = 0; i < size; i++) {
			temp[i] = components[i];
		}
		delete[] components;
		components = temp;
	}
	components[size] = part;
	size++;
}


template<typename T>
void Orders::push_back(T* part) {
	if (size == capacity) {
		capacity *= 2;
		Part** temp = new Part * [capacity];
		for (size_t i = 0; i < size; i++) {
			temp[i] = builds[i];
		}
		delete[] builds;
		builds = temp;
	}
	builds[size] = part;
	size++;
}
