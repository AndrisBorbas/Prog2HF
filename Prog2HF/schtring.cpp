#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS		//disable printf unsecure error
#pragma warning(disable : 4996)		//disable strlwr deprecated error
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#endif

#include <iostream>             
#include <cstring>             

#include "memtrace.h"
#include "schtring.h"

using std::cin;
using std::ios_base;

char* stolower(char* s) {
	char* p = s;
	while ((*p = tolower(*p))) p++;
	return s;
}

String::String(char ch) {
	len = 1;
	pData = new char[len + 1];
	pData[0] = ch;
	pData[1] = '\0';
}



String::String(const char* p) {
	len = strlen(p);
	pData = new char[len + 1];
	strcpy(pData, p);
}

String::String(const String& s1) {
	len = s1.len;
	pData = new char[len + 1];
	strcpy(pData, s1.pData);
}


String& String::operator=(const String& rhs_s) {
	if (this != &rhs_s) {
		delete[] pData;
		len = rhs_s.len;
		pData = new char[len + 1];
		strcpy(pData, rhs_s.pData);
	}
	return *this;
}


char& String::operator[](unsigned int idx) {
	if (idx >= len) throw "String: indexelesi hiba";
	return pData[idx];
}

const char& String::operator[](unsigned int idx) const {
	if (idx >= len) throw "String: indexelesi hiba";
	return pData[idx];
}

void String::removeFirstX(int x) {
	len = len - x;
	char* temp = new char[len + 1];
	for (int i = 0; i < len; i++) {
		temp[i] = pData[i + x];
	}
	temp[len] = '\0';
	delete[] pData;
	pData = temp;
}

String String::operator+(const String& rhs_s) const {
	String temp;
	temp.len = len + rhs_s.len;
	delete[]temp.pData;
	temp.pData = new char[temp.len + 1];
	strcpy(temp.pData, pData);
	strcat(temp.pData, rhs_s.pData);
	return temp;
}

bool String::operator==(String& rhs_s) {
	char* tempr = new char[rhs_s.length() + 1];
	strcpy(tempr, rhs_s.c_str());
	stolower(tempr);
	char* templ = new char[len + 1];
	strcpy(templ, pData);
	stolower(templ);
	bool temp = strcmp(templ, tempr);
	delete[] tempr;
	delete[] templ;
	return (!temp);
}

bool String::operator==(const char* rhs_s) {
	char* tempr = new char[strlen(rhs_s) + 1];
	strcpy(tempr, rhs_s);
	stolower(tempr);
	char* templ = new char[len + 1];
	strcpy(templ, pData);
	stolower(templ);
	bool temp = strcmp(templ, tempr);
	delete[] tempr;
	delete[] templ;
	return (!temp);
}

bool String::operator==(const char* rhs_s) const {
	char* tempr = new char[strlen(rhs_s) + 1];
	strcpy(tempr, rhs_s);
	stolower(tempr);
	char* templ = new char[len + 1];
	strcpy(templ, pData);
	stolower(templ);
	bool temp = strcmp(templ, tempr);
	delete[] tempr;
	delete[] templ;
	return (!temp);
}

String String::operator--(int a) {
	char* temp = new char[len];
	strncpy(temp, pData, len - 1);
	temp[len - 1] = '\0';
	delete[] pData;
	pData = temp;
	len--;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const String& s0) {
	os << s0.c_str();
	return os;
}

std::istream& operator>>(std::istream& is, String& s0) {
	unsigned char ch;
	s0 = String("");
	std::ios_base::fmtflags fl = is.flags();
	is.setf(ios_base::skipws);
	while (is >> ch) {
		is.unsetf(ios_base::skipws);
		if (isspace(ch)) {
			is.putback(ch);
			break;
		}
		else {
			s0 = s0 + ch;
		}
	}
	is.setf(fl);
	return is;
}
