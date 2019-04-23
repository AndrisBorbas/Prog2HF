#include "Inventory.h"



Part* loadPart(std::istream& is, TempInput& tmp, enum enumPart e) {
	switch (e)
	{
	case eCPU:
		LoadParams(is, tmp, 7);
		return (new CPU(tmp));
	case eGPU:
		LoadParams(is, tmp, 5);
		return (new GPU(tmp));
	case eMOBO:
		LoadParams(is, tmp, 6);
		return (new MOBO(tmp));
	case eRAM:
		LoadParams(is, tmp, 5);
		return (new RAM(tmp));
	case eCase:
		LoadParams(is, tmp, 4);
		return (new Case(tmp));
	case ePSU:
		LoadParams(is, tmp, 4);
		return (new PSU(tmp));
	case eSSD:
		LoadParams(is, tmp, 8);
		return (new SSD(tmp));
	case eHDD:
		LoadParams(is, tmp, 7);
		return (new HDD(tmp));
	}
	throw std::logic_error("how did you get here?");
}

void setEnum(String inst, enum enumPart& e)
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

void LoadParams(std::istream& is, TempInput& tmp, int const params) {
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
			tmp.instruction == "Multi-Threading:" || tmp.instruction == "SimultaneousMultiThreading" || tmp.instruction == "SimultaneousMulti-Threading" ||
			tmp.instruction == "SMT" || tmp.instruction == "HT")
		{
			String temp;
			is >> temp;
			if (temp == "yes" || temp == "true" || temp == "1") {
				tmp.multithreading = true;
			}
			if (temp == "no" || temp == "false" || temp == "0") {
				tmp.multithreading = false;
			}
			i++;
			continue;
		}
		if (tmp.instruction == "Size:" || tmp.instruction == "Memory:" || tmp.instruction == "MemorySize:" || tmp.instruction == "VRAM:" || tmp.instruction == "VideoMemory") {
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
		if (tmp.instruction == "FormFactor:") {
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
		if (tmp.instruction == "ReadSpeed:" || tmp.instruction == "Speed:") {
			is >> tmp.readspeed;
			i++;
			continue;
		}
		if (tmp.instruction == "WriteSpeed:" || tmp.instruction == "Speed:") {
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