#include "Builds.h"

#if defined(MEMTRACE) || defined(DMEMTRACE)
#include "memtrace.h"
#endif

void Build::save(std::ostream& os) const {
	os << std::endl;
	os << "Items: " << size << std::endl << std::endl;
	for (int i = 0; i < size; i++) {
		///class neve
		String name = typeid(*(*this)[i]).name();
		///class szó levétele a class neve elől
#ifdef _MSC_VER
		name.removeFirstX(6);
#endif
#ifndef _MSC_VER
		name.removeFirstX(1);
#endif
		os << name << ": \n\t" << typ << (*(*this)[i]) << std::endl;
	}
}

void Build::print(std::ostream& os) const {
	for (int i = 0; i < size; i++) {
		///class neve
		String name = typeid(*(*this)[i]).name();
		///class szó levétele a class neve elől
#ifdef _MSC_VER
		name.removeFirstX(6);
#endif
#ifndef _MSC_VER
		name.removeFirstX(1);
#endif
		os << "\t" << name << ": \t" << simple << (*(*this)[i]) << std::endl;
	}
	os << "\nTotal price: " << price << "USD";
}

void Build::load(std::fstream& is, Inventory& inventory, TempInput& tmp) {
	int i = 0, j;
	is >> j;
	while (i < j) {
		is >> tmp.instruction;
		is >> tmp.type;
		if (tmp.type[tmp.type.length() - 1] == ',') tmp.type--;
		int a = inventory.findbyType(tmp.type);
		if (a == -1)std::cerr << "Couldn't find " << tmp.type;
		push_back(inventory[a]);
		i++;
	}
}

void Orders::load(std::fstream& is, Inventory& inventory, TempInput& tmp) {
	Build* temp = new Build;
	temp->load(is, inventory, tmp);
	push_back(temp);
	is >> tmp.instruction;
	if (tmp.instruction[tmp.instruction.length() - 1] == ':') {
		String s;
		is >> s;
		if (s[s.length() - 1] == ',') s--;
		if (s == "yes" || s == "true" || s == "1") {
			this->completed[size - 1] = true;
		}
		if (s == "no" || s == "false" || s == "0") {
			this->completed[size - 1] = false;
		}
	}
}

void Orders::save(std::ostream& os) const {
	for (int i = 0; i < size; i++) {
		(builds[i])->save(os);
		os << "\nCompleted: " << std::boolalpha << completed[i];
		os << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
}

void Orders::print(std::ostream& os) const {
	for (int i = 0; i < size; i++) {
		os << "Order " << i + 101 << ": " << std::endl << *(builds[i]) << std::endl;
		os << "Completed: " << std::boolalpha << completed[i] << std::endl << std::endl;
	}
}
void Orders::print(simple_ostream& tos) const {
	for (int i = 0; i < size; i++) {
		tos.os << "Order " << i + 101 << ": Total price: " << builds[i]->get_price() << "USD" << std::endl;
	}
}

void Orders::complete(int idx) {
	completed[idx] = true;
	std::cout << "Order " << idx + 101 << ": " << std::endl << *(builds[idx]) << std::endl;
	std::cout << "Completed: " << std::boolalpha << completed[idx] << std::endl << std::endl;
}

void Orders::remove(int idx) {
	if (idx >= size)return;
	delete builds[idx];
	size -= 1;
	for (int i = idx; i < size; i++) {
		builds[i] = builds[i + 1];
		completed[i] = completed[i + 1];
	}
}


std::ostream& operator<<(std::ostream& os, const Build& b) {
	b.print(os);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Orders& o) {
	o.print(os);
	return os;
}
std::ostream& operator<<(simple_ostream tos, const Orders& o) {
	o.print(tos);
	return tos.os;
}
