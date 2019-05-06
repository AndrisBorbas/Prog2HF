#include "Inventory.h"

void Inventory::loadPart(std::fstream& is, TempInput& tmp, enumPart e) {
	switch (e)
	{
	case eCPU:
		loadParams(is, tmp, 7);
		this->push_back(new CPU(tmp), "CPU");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eGPU:
		loadParams(is, tmp, 5);
		this->push_back(new GPU(tmp), "GPU");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eMOBO:
		loadParams(is, tmp, 6);
		this->push_back(new MOBO(tmp), "Motherboard");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eRAM:
		loadParams(is, tmp, 5);
		this->push_back(new RAM(tmp), "RAM");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eCase:
		loadParams(is, tmp, 4);
		this->push_back(new Case(tmp), "Case");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case ePSU:
		loadParams(is, tmp, 4);
		this->push_back(new PSU(tmp), "Powersupply");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eSSD:
		loadParams(is, tmp, 8);
		this->push_back(new SSD(tmp), "SSD");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eHDD:
		loadParams(is, tmp, 7);
		this->push_back(new HDD(tmp), "HDD");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eInvalid:
		throw std::logic_error("how did you get here?");
	}
	throw std::logic_error("how did you get here?");
	return;
}

void Inventory::loadPart(std::istream& is, TempInput& tmp, enumPart e) {
	switch (e)
	{
	case eCPU:
		std::cout << "CPU selected\n\n";
		loadCPUParams(is, tmp);
		this->push_back(new CPU(tmp), "CPU");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eGPU:
		std::cout << "GPU selected\n\n";
		loadGPUParams(is, tmp);
		this->push_back(new GPU(tmp), "GPU");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eMOBO:
		std::cout << "MOBO selected\n\n";
		loadMOBOParams(is, tmp);
		this->push_back(new MOBO(tmp), "Motherboard");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eRAM:
		std::cout << "RAM selected\n\n";
		loadRAMParams(is, tmp);
		this->push_back(new RAM(tmp), "RAM");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eCase:
		std::cout << "Case selected\n\n";
		loadCaseParams(is, tmp);
		this->push_back(new Case(tmp), "Case");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case ePSU:
		std::cout << "PSU selected\n\n";
		loadPSUParams(is, tmp);
		this->push_back(new PSU(tmp), "Powersupply");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eSSD:
		std::cout << "SSD selected\n\n";
		loadSSDParams(is, tmp);
		this->push_back(new SSD(tmp), "SSD");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eHDD:
		std::cout << "HDD selected\n\n";
		loadHDDParams(is, tmp);
		this->push_back(new HDD(tmp), "HDD");
#ifdef _DEBUG
		std::cout << "Part loaded: " << *((*this)[size - 1]) << std::endl;
#endif 
		return;
	case eInvalid:
		throw std::logic_error("how did you get here?");
	}
	throw std::logic_error("how did you get here?");
	return;
}

void Inventory::save(std::ostream& os) {
	os << std::endl;
	for (int i = 0; i < size; i++) {
		///class neve
		String name = typeid(*(*this)[i]).name();
		///class szó levétele a class neve elől
		name.removeFirstX(6);
		os << name << ": \n\t" << (*(*this)[i]) << std::endl;
	}
}

void Inventory::print(std::ostream& os) {
	for (int i = 0; i < size; i++) {
		os << i + 101 << ": \t" << *(type + i) << ": \t" << utos << (*(*this)[i]) << std::endl;
	}
}

void Inventory::removePart(int a) {
	if (a >= size)return;
	delete stock[a];
	size -= 1;
	for (int i = a; i < size; i++) {
		stock[i] = stock[i + 1];
		*(type + i) = *(type + i + 1);
	}
}

template<typename T>
void Inventory::push_back(T* part, String name) {
	if (size == (int)capacity) {
		capacity *= 2;
		Part** temp = new Part * [capacity];
		for (int i = 0; i < size; i++) {
			temp[i] = stock[i];
		}
		delete[] stock;
		stock = temp;
		String* stemp = new String[capacity];
		for (int i = 0; i < size; i++) {
			*(stemp + i) = *(type + i);
		}
		delete[] type;
		type = stemp;
	}
	stock[size] = part;
	*(type + size) = name;
	size++;
}


void setEnumfromString(String inst, enumPart& e)
{
	if (inst == "CPU:") {
		e = eCPU;
		return;
	}
	if (inst == "GPU:") {
		e = eGPU;
		return;
	}
	if (inst == "MOBO:") {
		e = eMOBO;
		return;
	}
	if (inst == "RAM:") {
		e = eRAM;
		return;
	}
	if (inst == "Case:") {
		e = eCase;
		return;
	}
	if (inst == "PSU:") {
		e = ePSU;
		return;
	}
	if (inst == "SSD:") {
		e = eSSD;
		return;
	}
	if (inst == "HDD:") {
		e = eHDD;
		return;
	}
	e = eInvalid;
	return;
}

void loadParams(std::fstream& is, TempInput& tmp, int const params) {
	int i = 0;
	while (i < params) {
		is >> tmp.instruction;
		if (tmp.instruction == "Brand:") {
			is >> tmp.brand;
			if (tmp.brand[tmp.brand.length() - 1] == ',') tmp.brand--;
			i++;
			continue;
		}
		if (tmp.instruction == "Type:") {
			is >> tmp.type;
			if (tmp.type[tmp.type.length() - 1] == ',') tmp.type--;
			i++;
			continue;
		}
		if (tmp.instruction == "Price:") {
			is >> tmp.price;
			i++;
			continue;
		}
		if (tmp.instruction == "ClockSpeed:" || tmp.instruction == "Clock:" || tmp.instruction == "CLK:" || tmp.instruction == "BaseClock:") {
			is >> tmp.clk;
			i++;
			continue;
		}
		if (tmp.instruction == "Cores:") {
			is >> tmp.cores;
			i++;
			continue;
		}
		if (tmp.instruction == "Socket:") {
			is >> tmp.socket;
			if (tmp.socket[tmp.socket.length() - 1] == ',') tmp.socket--;
			i++;
			continue;
		}
		if (tmp.instruction == "HyperThreading:" || tmp.instruction == "Hyper-Threading:" || tmp.instruction == "MultiThreading:" ||
			tmp.instruction == "Multi-Threading:" || tmp.instruction == "SimultaneousMultiThreading:" || tmp.instruction == "SimultaneousMulti-Threading:" ||
			tmp.instruction == "SMT:" || tmp.instruction == "HT:")
		{
			String temp;
			is >> temp;
			if (temp[temp.length() - 1] == ',') temp--;
			if (temp == "yes" || temp == "true" || temp == "1") {
				tmp.multithreading = true;
			}
			if (temp == "no" || temp == "false" || temp == "0") {
				tmp.multithreading = false;
			}
			i++;
			continue;
		}
		if (tmp.instruction == "Size:" || tmp.instruction == "Memory:" || tmp.instruction == "MemorySize:" ||
			tmp.instruction == "VRAM:" || tmp.instruction == "VideoMemory" || tmp.instruction == "Capacity:") {
			is >> tmp.size;
			i++;
			continue;
		}
		if (tmp.instruction == "Chipset:") {
			is >> tmp.chipset;
			if (tmp.chipset[tmp.chipset.length() - 1] == ',') tmp.chipset--;
			i++;
			continue;
		}
		if (tmp.instruction == "FormFactor:" || tmp.instruction == "Factor:") {
			is >> tmp.formfactor;
			if (tmp.formfactor[tmp.formfactor.length() - 1] == ',') tmp.formfactor--;
			i++;
			continue;
		}
		if (tmp.instruction == "Wattage:") {
			is >> tmp.wattage;
			i++;
			continue;
		}
		if (tmp.instruction == "ReadSpeed:") {
			is >> tmp.readspeed;
			i++;
			continue;
		}
		if (tmp.instruction == "WriteSpeed:") {
			is >> tmp.writespeed;
			i++;
			continue;
		}
		if (tmp.instruction == "RPM:") {
			is >> tmp.rpm;
			i++;
			continue;
		}
		if (tmp.instruction == "FlashType:" || tmp.instruction == "Flash:") {
			is >> tmp.flashtype;
			if (tmp.flashtype[tmp.flashtype.length() - 1] == ',') tmp.flashtype--;
			i++;
			continue;
		}
	}
	return;
}

void loadBaseParams(std::istream& is, TempInput& tmp) {
	std::cout << "Brand: ";
	is >> tmp.brand;
	std::cout << "Type: ";
	is >> tmp.type;
	std::cout << "Price: ";
	is >> tmp.price;
}

void loadCPUParams(std::istream& is, TempInput& tmp) {
	loadBaseParams(is, tmp);
	std::cout << "Clock Speed: ";
	is >> tmp.clk;
	std::cout << "Cores: ";
	is >> tmp.cores;
	std::cout << "Socket: ";
	is >> tmp.socket;
	if (tmp.brand == "Intel")
		std::cout << "Does it support Hyper-Threading(yes or no): ";
	else
		std::cout << "Does it support Simultaneous Multithreading(yes or no): ";
	String temp;
	is >> temp;
	if (temp[temp.length() - 1] == ',') temp--;
	if (temp == "yes" || temp == "true" || temp == "1") {
		tmp.multithreading = true;
	}
	if (temp == "no" || temp == "false" || temp == "0") {
		tmp.multithreading = false;
	}
}

void loadGPUParams(std::istream& is, TempInput& tmp) {
	loadBaseParams(is, tmp);
	std::cout << "Clock speed: ";
	is >> tmp.clk;
	std::cout << "VRAM size: ";
	is >> tmp.size;
}

void loadMOBOParams(std::istream& is, TempInput& tmp) {
	loadBaseParams(is, tmp);
	std::cout << "Socket: ";
	is >> tmp.socket;
	std::cout << "Chipset: ";
	is >> tmp.chipset;
	std::cout << "Form factor: ";
	is >> tmp.formfactor;
}

void loadRAMParams(std::istream& is, TempInput& tmp) {
	loadBaseParams(is, tmp);
	std::cout << "Speed: ";
	is >> tmp.clk;
	std::cout << "Size: ";
	is >> tmp.size;
}

void loadCaseParams(std::istream& is, TempInput& tmp) {
	loadBaseParams(is, tmp);
	std::cout << "Form factor: ";
	is >> tmp.formfactor;
}

void loadPSUParams(std::istream& is, TempInput& tmp) {
	loadBaseParams(is, tmp);
	std::cout << "Wattage: ";
	is >> tmp.wattage;
}

void loadSSDParams(std::istream& is, TempInput& tmp) {
	loadBaseParams(is, tmp);
	std::cout << "Capacity: ";
	is >> tmp.size;
	std::cout << "Read speed: ";
	is >> tmp.readspeed;
	std::cout << "Write speed: ";
	is >> tmp.writespeed;
	std::cout << "Form factor: ";
	is >> tmp.formfactor;
	std::cout << "Flash layers: ";
	is >> tmp.flashtype;
}

void loadHDDParams(std::istream& is, TempInput& tmp) {
	loadBaseParams(is, tmp);
	std::cout << "Capacity: ";
	is >> tmp.size;
	std::cout << "Read speed: ";
	is >> tmp.readspeed;
	std::cout << "Write speed: ";
	is >> tmp.writespeed;
	std::cout << "RPM: ";
	is >> tmp.rpm;
}