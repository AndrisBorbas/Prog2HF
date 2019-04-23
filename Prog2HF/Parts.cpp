#include "Parts.h"

void Part::print(std::ostream& os) const {
	os << "Brand: " << brand << ", Type: " << type << ", Price: " << price << " USD, ";
}

void CPU::print(std::ostream& os) const {
	Part::print(os);
	os << "Base clock: " << clk << " MHz, Number of Cores: " << cores << ", Socket: " << socket;
	if (brand == "AMD") {
		os << ", Supports Simultaneous Multithreading: ";
	}
	else {
		os << ", Supports Hyper-Threading: ";
	}
	if (multithreading) {
		os << "Yes";
	}
	else {
		os << "No";
	}
}

void GPU::print(std::ostream& os) const {
	Part::print(os);
	os << "Base Clock: " << clk << ", Video Memory: " << vram << " GB";
}

void MOBO::print(std::ostream& os) const {
	Part::print(os);
	os << "Socket: " << socket << ", Chipset: " << chipset << ", Form factor: " << formfactor;
}

void RAM::print(std::ostream& os)const {
	Part::print(os);
	os << "Base Clock: " << clk << ", Memory: " << size << " GB";
}

void Case::print(std::ostream& os)const {
	Part::print(os);
	os << "Form factor: " << formfactor;
}

void PSU::print(std::ostream& os)const {
	Part::print(os);
	os << "Wattage: " << wattage << " W";
}

void Storage::print(std::ostream& os)const {
	Part::print(os);
	os << "Capacity: " << size << " GB, Random Read Speed: " << readspeed << " MB/s, Random Write Speed: " << writespeed << " MB/s";
}

void SSD::print(std::ostream& os)const {
	Storage::print(os);
	os << "Form factor: " << formfactor << ", Flash: " << flashtype;
}

void HDD::print(std::ostream& os)const {
	Storage::print(os);
	os << "RPM: " << rpm << " rpm";
}

void CPU::burn()const {
	std::cout << "\n\n\nBurn\n\n\n";
}

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
