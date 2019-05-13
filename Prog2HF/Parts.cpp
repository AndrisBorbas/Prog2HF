#include "Parts.h"

#if defined(MEMTRACE) || defined(DMEMTRACE)
#include "memtrace.h"
#endif

void Part::print(std::ostream& os) const {
	os << "Brand: " << brand << ", Type: " << type << ", Price: " << price << " USD, ";
}
void Part::print(utos_ostream& tos) const {
	tos.os << "Brand: " << utos << brand << ", Type: " << utos << type << ", Price: " << price << " USD, ";
}
void Part::print(simple_ostream& tos) const {
	tos.os << utos << brand << " " << utos << type << ", \t" << price << " USD";
}
void Part::print(typ_ostream& tos) const {
	tos.os << type;
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
void CPU::print(simple_ostream& tos) const {
	Part::print(tos);
}
void CPU::print(typ_ostream& tos) const {
	Part::print(tos);
}

void GPU::print(std::ostream& os) const {
	Part::print(os);
	os << "Base Clock: " << clk << " MHz, Video Memory: " << vram << " GB";
}
void GPU::print(utos_ostream& tos) const {
	Part::print(tos);
	tos.os << "Base Clock: " << clk << " MHz, Video Memory: " << vram << " GB";
}
void GPU::print(simple_ostream& tos) const {
	Part::print(tos);
}
void GPU::print(typ_ostream& tos) const {
	Part::print(tos);
}

void MOBO::print(std::ostream& os) const {
	Part::print(os);
	os << "Socket: " << socket << ", Chipset: " << chipset << ", Form factor: " << formfactor;
}
void MOBO::print(utos_ostream& tos) const {
	Part::print(tos);
	tos.os << "Socket: " << utos << socket << ", Chipset: " << utos << chipset << ", Form factor: " << utos << formfactor;
}
void MOBO::print(simple_ostream& tos) const {
	Part::print(tos);
}
void MOBO::print(typ_ostream& tos) const {
	Part::print(tos);
}

void RAM::print(std::ostream& os)const {
	Part::print(os);
	os << "Base Clock: " << clk << ", Memory: " << size << " GB";
}
void RAM::print(utos_ostream& tos)const {
	Part::print(tos);
	tos.os << "Base Clock: " << clk << ", Memory: " << size << " GB";
}
void RAM::print(simple_ostream& tos) const {
	Part::print(tos);
}
void RAM::print(typ_ostream& tos) const {
	Part::print(tos);
}

void Case::print(std::ostream& os)const {
	Part::print(os);
	os << "Form factor: " << formfactor;
}
void Case::print(utos_ostream& tos)const {
	Part::print(tos);
	tos.os << "Form factor: " << utos << formfactor;
}
void Case::print(simple_ostream& tos) const {
	Part::print(tos);
}
void Case::print(typ_ostream& tos) const {
	Part::print(tos);
}

void PSU::print(std::ostream& os)const {
	Part::print(os);
	os << "Wattage: " << wattage << " W";
}
void PSU::print(utos_ostream& tos)const {
	Part::print(tos);
	tos.os << "Wattage: " << wattage << " W";
}
void PSU::print(simple_ostream& tos) const {
	Part::print(tos);
}
void PSU::print(typ_ostream& tos) const {
	Part::print(tos);
}

void Storage::print(std::ostream& os)const {
	Part::print(os);
	os << "Capacity: " << size << " GB, ReadSpeed: " << readspeed << " MB/s, WriteSpeed: " << writespeed << " MB/s, ";
}
void Storage::print(utos_ostream& tos)const {
	Part::print(tos);
	tos.os << "Capacity: " << size << " GB, ReadSpeed: " << readspeed << " MB/s, WriteSpeed: " << writespeed << " MB/s, ";
}
void Storage::print(simple_ostream& tos) const {
	Part::print(tos);
}
void Storage::print(typ_ostream& tos) const {
	Part::print(tos);
}

void SSD::print(std::ostream& os)const {
	Storage::print(os);
	os << "Form factor: " << formfactor << ", Flash: " << flashtype;
}
void SSD::print(utos_ostream& tos)const {
	Storage::print(tos);
	tos.os << "Form factor: " << utos << formfactor << ", Flash: " << utos << flashtype;
}
void SSD::print(simple_ostream& tos) const {
	Part::print(tos);
}
void SSD::print(typ_ostream& tos) const {
	Part::print(tos);
}

void HDD::print(std::ostream& os)const {
	Storage::print(os);
	os << "RPM: " << rpm << " rpm";
}
void HDD::print(utos_ostream& tos)const {
	Storage::print(tos);
	tos.os << "RPM: " << rpm << " rpm";
}
void HDD::print(simple_ostream& tos) const {
	Part::print(tos);
}
void HDD::print(typ_ostream& tos) const {
	Part::print(tos);
}


std::ostream& operator<<(std::ostream& os, const Part& p) {
	p.print(os);
	return os;
}
std::ostream& operator<<(utos_ostream tos, const Part& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(simple_ostream tos, const Part& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const Part& p) {
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
std::ostream& operator<<(simple_ostream tos, const CPU& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const CPU& p) {
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
std::ostream& operator<<(simple_ostream tos, const GPU& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const GPU& p) {
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
std::ostream& operator<<(simple_ostream tos, const MOBO& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const MOBO& p) {
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
std::ostream& operator<<(simple_ostream tos, const RAM& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const RAM& p) {
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
std::ostream& operator<<(simple_ostream tos, const Case& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const Case& p) {
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
std::ostream& operator<<(simple_ostream tos, const PSU& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const PSU& p) {
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
std::ostream& operator<<(simple_ostream tos, const Storage& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const Storage& p) {
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
std::ostream& operator<<(simple_ostream tos, const SSD& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const SSD& p) {
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
std::ostream& operator<<(simple_ostream tos, const HDD& p) {
	p.print(tos);
	return tos.os;
}
std::ostream& operator<<(typ_ostream tos, const HDD& p) {
	p.print(tos);
	return tos.os;
}


void setEnumfromString(String s0, enumPart& e)
{
	if (s0 == "CPU:") {
		e = eCPU;
		return;
	}
	if (s0 == "GPU:") {
		e = eGPU;
		return;
	}
	if (s0 == "MOBO:") {
		e = eMOBO;
		return;
	}
	if (s0 == "RAM:") {
		e = eRAM;
		return;
	}
	if (s0 == "Case:") {
		e = eCase;
		return;
	}
	if (s0 == "PSU:") {
		e = ePSU;
		return;
	}
	if (s0 == "SSD:") {
		e = eSSD;
		return;
	}
	if (s0 == "HDD:") {
		e = eHDD;
		return;
	}
	e = eInvalid;
	return;
}