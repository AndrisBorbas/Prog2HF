#pragma once

#include "main.h"

///Test the if the parts file could be opened
void test1(std::fstream& partsFile, const char partsfilename[52]);
///Test the non case sensitive String compare
bool test3(String test1, String test2);
///Test the string shortener
bool test4(String asd, const char* test);
///Test the sring first x character removal
bool test5(String asd, const char* test);