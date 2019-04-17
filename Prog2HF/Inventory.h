#pragma once

#include "main.h"

class Inventory {

};

Part* loadPart(std::istream& is, TempInput & tmp, enum enumPart e);

void setEnum(String inst, enum enumPart & e);

void LoadParams(std::istream & is, TempInput & tmp, int const params);