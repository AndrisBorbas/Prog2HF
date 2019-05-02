#pragma once

#include "main.h"

///Test the if the parts file could be opened
void test1(std::fstream& partsFile, const char partsfilename[52]);
///Test whether the heterogenous collection contains the derived classes
bool test2(Inventory & inventory);
///Test the non case sensitive String compare
bool test3(String test1, String test2);
///Test the string shortener
bool test4(String asd, const char* test);