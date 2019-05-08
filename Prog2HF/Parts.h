#pragma once

#ifdef MEMTRACE
#include "memtrace.h"
#endif
#include "schtring.hpp"
#include <typeinfo>
#include <cctype>
//#include "Compatibility.h"

///Betöltéshez segítő
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

//Doxygen miatt a doc kommentek a kövi sorra vonatkoznak

///Lehetséges inputokat tárolja adatokkal való konstruáláshoz
struct TempInput {
	///Mihez tartozik a változó
	String instruction;		///Kompatibilitás lista neve
	String clname;			///Gyártó
	String brand;			///Típus
	String type;			///Ár
	int price;				///Foglalat
	String socket;			///Órajel
	int clk;				///Magok száma
	int cores;				///Multithreading support
	bool multithreading;	///Chipset
	String chipset;			///Méret szabvány
	String formfactor;		///Memória méret
	int size;				///Teljesítmény
	int wattage;			///Olvasási sebesség
	int readspeed;			///Írási sebesség
	int writespeed;			///Flash csip típusa
	String flashtype;		///Fordulatszám
	int rpm;
};


///Alap alkatrész típus
class Part {
protected:
	///Gyártó
	String brand;	///Típus
	String type;	///Ár
	int price;
public:
	Part(String brand = "", String type = "", int price = 0) : brand(brand), type(type), price(price) {
		this->brand[0] = static_cast<char>(toupper(this->brand[0]));
	}
	virtual ~Part() {}

	virtual int get_price() { return price; }
	virtual String get_type() { return type; }

	virtual void print(std::ostream& os) const;
	virtual void print(utos_ostream& tos) const;
	virtual void print(simple_ostream& tos) const;
	virtual void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const Part&);
std::ostream& operator<<(utos_ostream, const Part&);
std::ostream& operator<<(simple_ostream, const Part&);
std::ostream& operator<<(typ_ostream, const Part&);


///Processzor
class CPU : public Part {
	///Órajel
	int clk;				///Magok száma
	int cores;				///Foglalat
	String socket;			///Multithreading support
	bool multithreading;
public:
	explicit CPU(String brand, String type, int price, int clk, int cores, String socket, bool multithreading) : Part(brand, type, price),
		clk(clk), cores(cores), socket(socket), multithreading(multithreading) {}
	explicit CPU(TempInput& tmp) :Part(tmp.brand, tmp.type, tmp.price), clk(tmp.clk), cores(tmp.cores), socket(tmp.socket), multithreading(tmp.multithreading) {}

	void print(std::ostream& os) const;
	void print(utos_ostream& tos) const;
	void print(simple_ostream& tos) const;
	void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const CPU&);
std::ostream& operator<<(utos_ostream, const CPU&);
std::ostream& operator<<(simple_ostream, const CPU&);
std::ostream& operator<<(typ_ostream, const CPU&);


///Videókártya
class GPU : public Part {
	///Órajel
	int clk;	///Videómemória
	int vram;
public:
	explicit GPU(String brand, String type, int price, int clk, int vram) : Part(brand, type, price), clk(clk), vram(vram) {}
	explicit GPU(TempInput& tmp) :Part(tmp.brand, tmp.type, tmp.price), clk(tmp.clk), vram(tmp.size) {}

	void print(std::ostream& os) const;
	void print(utos_ostream& tos) const;
	void print(simple_ostream& tos) const;
	void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const GPU&);
std::ostream& operator<<(utos_ostream, const GPU&);
std::ostream& operator<<(simple_ostream, const GPU&);
std::ostream& operator<<(typ_ostream, const GPU&);


///Alaplap
class MOBO : public Part {
	///Foglalat
	String socket;		///Chipset
	String chipset;		///Méret szabvány
	String formfactor;
public:
	explicit MOBO(String brand, String type, int price, String socket, String chipset, String formfactor) : Part(brand, type, price),
		socket(socket), chipset(chipset), formfactor(formfactor) {}
	explicit MOBO(TempInput& tmp) :Part(tmp.brand, tmp.type, tmp.price), socket(tmp.socket), chipset(tmp.chipset), formfactor(tmp.formfactor) {}

	void print(std::ostream& os) const;
	void print(utos_ostream& tos) const;
	void print(simple_ostream& tos) const;
	void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const MOBO&);
std::ostream& operator<<(utos_ostream, const MOBO&);
std::ostream& operator<<(simple_ostream, const MOBO&);
std::ostream& operator<<(typ_ostream, const MOBO&);


///Memória
class RAM : public Part {
	///Órajel
	int clk;	///Memória
	int size;
public:
	explicit RAM(String brand, String type, int price, int clk, int size) : Part(brand, type, price), clk(clk), size(size) {}
	explicit RAM(TempInput& tmp) :Part(tmp.brand, tmp.type, tmp.price), clk(tmp.clk), size(tmp.size) {}

	void print(std::ostream& os) const;
	void print(utos_ostream& tos) const;
	void print(simple_ostream& tos) const;
	void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const RAM&);
std::ostream& operator<<(utos_ostream, const RAM&);
std::ostream& operator<<(simple_ostream, const RAM&);
std::ostream& operator<<(typ_ostream, const RAM&);


///Ház
class Case : public Part {
	///Méret szabvány
	String formfactor;
public:
	explicit Case(String brand, String type, int price, String formfactor) : Part(brand, type, price), formfactor(formfactor) {}
	explicit Case(TempInput& tmp) :Part(tmp.brand, tmp.type, tmp.price), formfactor(tmp.formfactor) {}

	void print(std::ostream& os) const;
	void print(utos_ostream& tos) const;
	void print(simple_ostream& tos) const;
	void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const Case&);
std::ostream& operator<<(utos_ostream, const Case&);
std::ostream& operator<<(simple_ostream, const Case&);
std::ostream& operator<<(typ_ostream, const Case&);


///Táp
class PSU : public Part {
	///Teljesítmény
	int wattage;
public:
	explicit PSU(String brand, String type, int price, int wattage) : Part(brand, type, price), wattage(wattage) {}
	explicit PSU(TempInput& tmp) :Part(tmp.brand, tmp.type, tmp.price), wattage(tmp.wattage) {}

	void print(std::ostream& os) const;
	void print(utos_ostream& tos) const;
	void print(simple_ostream& tos) const;
	void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const PSU&);
std::ostream& operator<<(utos_ostream, const PSU&);
std::ostream& operator<<(simple_ostream, const PSU&);
std::ostream& operator<<(typ_ostream, const PSU&);


///Tárhely alap
class Storage : public Part {
protected:
	///Méret
	int size;			///Olvasási sebesség
	int readspeed;		///Írási sebesség
	int writespeed;
public:
	explicit Storage(String brand, String type, int price, int size, int readspeed, int writespeed) : Part(brand, type, price),
		size(size), readspeed(readspeed), writespeed(writespeed) {}

	virtual void print(std::ostream& os) const;
	virtual void print(utos_ostream& tos) const;
	virtual void print(simple_ostream& tos) const;
	virtual void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const Storage&);
std::ostream& operator<<(utos_ostream, const Storage&);
std::ostream& operator<<(simple_ostream, const Storage&);
std::ostream& operator<<(typ_ostream, const Storage&);


///SSD
class SSD : public Storage {
	///Szabvány
	String formfactor;	///Flash csip típusa
	String flashtype;
public:
	explicit SSD(String brand, String type, int price, int size, int readspeed, int writespeed, String formfactor, String flashtype) :
		Storage(brand, type, price, size, readspeed, writespeed), formfactor(formfactor), flashtype(flashtype) {}
	explicit SSD(TempInput& tmp) :Storage(tmp.brand, tmp.type, tmp.price, tmp.size, tmp.readspeed, tmp.writespeed), formfactor(tmp.formfactor), flashtype(tmp.flashtype) {}

	void print(std::ostream& os) const;
	void print(utos_ostream& tos) const;
	void print(simple_ostream& tos) const;
	void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const SSD&);
std::ostream& operator<<(utos_ostream, const SSD&);
std::ostream& operator<<(simple_ostream, const SSD&);
std::ostream& operator<<(typ_ostream, const SSD&);


///Merevlemez
class HDD : public Storage {
	///Fordulatszám
	int rpm;
public:
	explicit HDD(String brand, String type, int price, int size, int readspeed, int writespeed, int rpm) :
		Storage(brand, type, price, size, readspeed, writespeed), rpm(rpm) {}
	explicit HDD(TempInput& tmp) :Storage(tmp.brand, tmp.type, tmp.price, tmp.size, tmp.readspeed, tmp.writespeed), rpm(tmp.rpm) {}

	void print(std::ostream& os) const;
	void print(utos_ostream& tos) const;
	void print(simple_ostream& tos) const;
	void print(typ_ostream& tos) const;
};

std::ostream& operator<<(std::ostream&, const HDD&);
std::ostream& operator<<(utos_ostream, const HDD&);
std::ostream& operator<<(simple_ostream, const HDD&);
std::ostream& operator<<(typ_ostream, const HDD&);


///Enumot állít be gy stringből
void setEnumfromString(String inst, enumPart&);