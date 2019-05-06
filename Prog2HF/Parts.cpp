#include "Parts.h"

void Part::print(std::ostream& os) const {
	os << "Brand: " << brand << ", Type: " << type << ", Price: " << price << " USD, ";
}
void Part::print(utos_ostream& tos) const {
	tos.os << "Brand: " << utos << brand << ", Type: " << utos << type << ", Price: " << price << " USD, ";
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
void CPU::print(utos_ostream& tos) const {
	Part::print(tos);
	tos.os << "Base clock: " << clk << " MHz, Number of Cores: " << cores << ", Socket: " << socket;
	if (brand == "AMD") {
		tos.os << ", Supports Simultaneous Multithreading: ";
	}
	else {
		tos.os << ", Supports Hyper-Threading: ";
	}
	if (multithreading) {
		tos.os << "Yes";
	}
	else {
		tos.os << "No";
	}
}

void GPU::print(std::ostream& os) const {
	Part::print(os);
	os << "Base Clock: " << clk << " MHz, Video Memory: " << vram << " GB";
}
void GPU::print(utos_ostream& tos) const {
	Part::print(tos);
	tos.os << "Base Clock: " << clk << " MHz, Video Memory: " << vram << " GB";
}

void MOBO::print(std::ostream& os) const {
	Part::print(os);
	os << "Socket: " << socket << ", Chipset: " << chipset << ", Form factor: " << formfactor;
}
void MOBO::print(utos_ostream& tos) const {
	Part::print(tos);
	tos.os << "Socket: " << utos << socket << ", Chipset: " << utos << chipset << ", Form factor: " << utos << formfactor;
}

void RAM::print(std::ostream& os)const {
	Part::print(os);
	os << "Base Clock: " << clk << ", Memory: " << size << " GB";
}
void RAM::print(utos_ostream& tos)const {
	Part::print(tos);
	tos.os << "Base Clock: " << clk << ", Memory: " << size << " GB";
}

void Case::print(std::ostream& os)const {
	Part::print(os);
	os << "Form factor: " << formfactor;
}
void Case::print(utos_ostream& tos)const {
	Part::print(tos);
	tos.os << "Form factor: " << utos << formfactor;
}

void PSU::print(std::ostream& os)const {
	Part::print(os);
	os << "Wattage: " << wattage << " W";
}
void PSU::print(utos_ostream& tos)const {
	Part::print(tos);
	tos.os << "Wattage: " << wattage << " W";
}

void Storage::print(std::ostream& os)const {
	Part::print(os);
	os << "Capacity: " << size << " GB, ReadSpeed: " << readspeed << " MB/s, WriteSpeed: " << writespeed << " MB/s, ";
}
void Storage::print(utos_ostream& tos)const {
	Part::print(tos);
	tos.os << "Capacity: " << size << " GB, ReadSpeed: " << readspeed << " MB/s, WriteSpeed: " << writespeed << " MB/s, ";
}

void SSD::print(std::ostream& os)const {
	Storage::print(os);
	os << "Form factor: " << formfactor << ", Flash: " << flashtype;
}
void SSD::print(utos_ostream& tos)const {
	Storage::print(tos);
	tos.os << "Form factor: " << utos << formfactor << ", Flash: " << utos << flashtype;
}

void HDD::print(std::ostream& os)const {
	Storage::print(os);
	os << "RPM: " << rpm << " rpm";
}
void HDD::print(utos_ostream& tos)const {
	Storage::print(tos);
	tos.os << "RPM: " << rpm << " rpm";
}

std::ostream& operator<<(std::ostream& os, const Part& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const Part& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const CPU& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const CPU& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const GPU& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const GPU& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const MOBO& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const MOBO& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const RAM& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const RAM& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const Case& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const Case& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const PSU& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const PSU& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const Storage& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const Storage& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const SSD& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const SSD& p) {
	p.print(tos);
	return tos.os;
}

std::ostream& operator<<(std::ostream& os, const HDD& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const HDD& p) {
	p.print(tos);
	return tos.os;
}

