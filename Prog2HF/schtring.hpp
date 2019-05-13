#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS		//disable printf unsecure error
#pragma warning(disable : 4996)		//disable strlwr deprecated error
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#endif

#if defined(MEMTRACE) || defined(DMEMTRACE)
#include "memtrace.h"
#endif


#include <iostream>             
#include <cstring>
#include <ctype.h>

///szóközösítő toggle
struct utos_t {};
///csak paraméter toggle
struct simple_t {};
///csak típus toggle
struct typ_t {};

///szóközösítő toggle
constexpr utos_t utos;
///csak paraméter toggle
constexpr simple_t simple;
///csak típus toggle
constexpr typ_t typ;

///szóközösítő stream manipulator
struct utos_ostream {
	std::ostream& os;
};
///csak paraméter stream manipulator
struct simple_ostream {
	std::ostream& os;
};
///csak típus stream manipulator
struct typ_ostream {
	std::ostream& os;
};

///szóközösítő stream manipulator
inline utos_ostream operator<<(std::ostream& os, utos_t) { return { os }; }
///csak paraméter stream manipulator
inline simple_ostream operator<<(std::ostream& os, simple_t) { return { os }; }
///csak típus stream manipulator
inline typ_ostream operator<<(std::ostream& os, typ_t) { return { os }; }

///szóközösítő ostream
template <typename T>
std::ostream& operator<<(utos_ostream tos, const T& v) { return tos.os << v; }
///csak paraméter ostream
template <typename T>
std::ostream& operator<<(simple_ostream tos, const T& v) { return tos.os << v; }
///csak paraméter ostream
template <typename T>
std::ostream& operator<<(typ_ostream tos, const T& v) { return tos.os << v; }

///char tömb kisbetűsítése
char* stolower(char* s);

class String {
	char* pData;         /// pointer az adatra
	size_t len;    /// hossz lezáró nulla nélkül
public:
	/// Visszaadja a string hosszát
	size_t size() const { return len; }
	/// Visszaadja a string hosszát
	size_t length() const { return len; }

	/// Default konstruktor
	String() :pData(0), len(0) {}

	/// Konstruktor: egy char karakterre
	String(char ch);

	/// Konstruktor: egy karakter tömbre
	String(const char* p);

	/// Konstruktor: egy másik Stringre
	String(const String& s1);

	/// C-stringet ad vissza
	const char* c_str() const { if (pData) return pData; else return ""; }

	///Destruktor
	~String() { delete[] pData; }

	/// Egyenlőség operator
	String& operator=(const String& rhs_s);

	/// Pluszegyenlő operator
	String& operator+=(const String& rhs_s) {
		*this = *this + rhs_s;
		return *this;
	}

	/// string + string
	String operator+(const String& rhs_s) const;

	/// string + karakter
	String operator+(char rhs_c) { return *this + String(rhs_c); }

	/// hasonlító operator stringgel
	bool operator==(String& rhs_s) const;
	bool operator==(const String& rhs_s) const;
	/// hasonlító operator char tömbbel
	bool operator==(const char* rhs_s);
	bool operator==(const char* rhs_s) const;

	/// kitörli az utolsó karaktert a stringből
	String operator--(int a);

	/// index operator
	char& operator[](unsigned int idx);
	/// index operator
	const char& operator[](unsigned int idx) const;

	/// törli a stringben lévő karaktereket
	void erase() { *this = ""; }

	///törli az első x karaktert a stringből
	void removeFirstX(int x);
};

///karakter + string
inline String operator+(char ch, const String& str) { return String(ch) + str; }

///inserter operator
std::ostream& operator<<(std::ostream& os, const String& s0);

///extractor operator
std::istream& operator>>(std::istream& is, String& s0);

///alsóvonást szóközzé alakító kiírás
std::ostream& operator<<(utos_ostream tos, const String& s0);