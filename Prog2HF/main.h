#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS		//disable printf unsecure error
#pragma warning(disable : 4996)		//disable strlwr deprecated error
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#endif

#include <chrono>
#include <thread>

#if defined(MEMTRACE) || defined(DMEMTRACE)
#include "memtrace.h"
#endif

#include "schtring.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <limits>
#include "Parts.h"
#include "Inventory.h"
#include "Builds.h"
#include "Menu.h"
#include "atest.h"

///entrypoint
int main(int argc, char** argv);

///elmenti a program módosításait
template <typename T>
void save(std::fstream&, std::fstream&, T&, std::streampos&, const char*, const char*);
