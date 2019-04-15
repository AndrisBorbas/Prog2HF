#include "Parts.h"

std::ostream& operator<<(std::ostream& os, const Part& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(std::ostream& os, const CPU& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(std::ostream& os, const GPU& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(std::ostream& os, const MOBO& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(std::ostream& os, const RAM& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(std::ostream& os, const Case& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(std::ostream& os, const PSU& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(std::ostream& os, const SSD& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(std::ostream& os, const HDD& p) {
	p.print(os);
	return os;
}


void Part::print(std::ostream & os) const {
	os << "Brand: " << brand << ", Type: " << type << ", Price: " << price << ".- , ";
}

void CPU::print(std::ostream & os) const {
	Part::print(os);
	os << "Base clock: " << clk << " MHz, Number of Cores: " << cores << ", Socket: " << socket;
	if (brand == "AMD") {
		os << ", Supports Simultaneous Multithreading: " << std::boolalpha << multithreading;
	}
	else {
		os << ", Supports Hyper-Threading: " << std::boolalpha << multithreading;
	}
}
