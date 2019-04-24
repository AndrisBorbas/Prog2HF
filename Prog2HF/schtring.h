#pragma once

#include <iostream>             
#include <cstring>
#include <ctype.h>

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
	bool operator==(String& rhs_s);
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
};

///inserter operator
std::ostream& operator<<(std::ostream& os, const String& s0);

///extractor operator
std::istream& operator>>(std::istream& is, String& s0);

///karakter + string
inline String operator+(char ch, const String& str) { return String(ch) + str; }