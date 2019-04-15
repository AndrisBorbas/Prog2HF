#pragma once

#include "Parts.h"

class Inventory {

};

void loadCPU(std::istream& is, Part** inventory, TempInput & tmp) {
	int i = 0;
	while (i<7) {
		is >> tmp.instruction;
		if (tmp.instruction == "Brand:") {
			is >> tmp.brand;
			i++;
			continue;
		}
		if (tmp.instruction == "Type:") {
			is >> tmp.type;
			i++;
			continue;
		}
		if (tmp.instruction == "Price:") {
			is >> tmp.price;
			i++;
			continue;
		}
		if (tmp.instruction == "ClockSpeed:" || tmp.instruction == "Speed:" || tmp.instruction == "Clock:" || tmp.instruction == "CLK:" || tmp.instruction == "BaseClock:") {
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
			i++;
			continue;
		}
		if (tmp.instruction == "HyperThreading:" || tmp.instruction == "Hyper-Threading:" || tmp.instruction == "MultiThreading:" || tmp.instruction == "Multi-Threading:") {
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
	}
	CPU* asd = new CPU(tmp.brand, tmp.type, tmp.price, tmp.clk, tmp.cores, tmp.socket, tmp.multithreading);
	inventory[0]=asd;
}