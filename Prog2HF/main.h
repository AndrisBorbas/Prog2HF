#pragma once

#include "schtring.h"
#include <iostream>
#include <fstream>
#include "Compatibility.h"
#include "Parts.h"
#include "Inventory.h"
#include "atest.h"

enum enumPart {
	eInvalid = 0,
	eCPU = 1,
	eGPU = 2,
	eMOBO = 3,
	eRAM = 4,
	eCase = 5,
	ePSU = 6,
	eSSD = 7,
	eHDD = 8
};

int main(int argc, char** argv);