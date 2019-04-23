#pragma once

#include "main.h"

class Inventory {

};

Part* loadPart(std::istream& is, TempInput & tmp, enum enumPart);

void setEnum(String inst, enum enumPart &);

void LoadParams(std::istream & is, TempInput & tmp, int const params);