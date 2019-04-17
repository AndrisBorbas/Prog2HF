#pragma once

#include "schtring.h"
#include "Compatibility.h"
#include <cctype>

struct TempInput {
	String instruction;		///Mihez tartozik a változó
	String clname;			///Kompatibilitás lista neve
	String brand;			///Gyártó
	String type;			///Típus
	int price;				///Ár
	String socket;			///Foglalat
	int clk;				///Órajel
	int cores;				///Magok száma
	bool multithreading;	///Multithreading support
	String chipset;			///Chipset
	String formfactor;		///Méret szabvány
	int size;				///Memória méret
	String wattage;			///Teljesítmény
	int readspeed;			///Olvasási sebesség
	int writespeed;			///Írási sebesség
	String flashtype;		///Flash csip típusa
	int rpm;				///Fordulatszám
};

class Part {
protected:
	String brand;	///Gyártó
	String type;	///Típus
	int price;		///Ár
public:
	Part(String brand = "", String type = "", int price = 0) : brand(brand), type(type), price(price) {
		this->brand[0] = static_cast<char>(toupper(this->brand[0]));
	}
	virtual ~Part() {}

	String get_brand() {
		return brand;
	}
	String get_type() {
		return type;
	}
	int get_price() {
		return price;
	}

	virtual void print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream&, const Part&);

class CPU : public Part {
	String socket;			///Foglalat
	int clk;				///Órajel
	int cores;				///Magok száma
	bool multithreading;	///Multithreading support
public:
	explicit CPU(String brand, String type, int price, int clk, int cores, String socket, bool multithreading) : Part(brand, type, price),
		clk(clk), cores(cores), socket(socket), multithreading(multithreading) {}
	explicit CPU(TempInput & tmp) :Part(tmp.brand, tmp.type, tmp.price), clk(tmp.clk), cores(tmp.cores), socket(tmp.socket), multithreading(tmp.multithreading) {}

	void print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream&, const CPU&);

class GPU : public Part {
	int clk;	///Órajel
	int vram;	///Videómemória
public:
	explicit GPU(String brand, String type, int price, int clk, int vram) : Part(brand, type, price), clk(clk), vram(vram) {}
	explicit GPU(TempInput & tmp) :Part(tmp.brand, tmp.type, tmp.price), clk(tmp.clk), vram(tmp.size) {}

	virtual void print(std::ostream& os) const {
		Part::print(os);
		os << clk << vram;
	}
};

std::ostream& operator<<(std::ostream&, const GPU&);

class MOBO : public Part {
	String socket;		///Foglalat
	String chipset;		///Chipset
	String formfactor;	///Méret szabvány
public:
	explicit MOBO(String brand, String type, int price, String socket, String chipset, String formfactor) : Part(brand, type, price),
		socket(socket), chipset(chipset), formfactor(formfactor) {}
	explicit MOBO(TempInput tmp) :Part(tmp.brand, tmp.type, tmp.price), socket(tmp.socket), chipset(tmp.chipset), formfactor(tmp.formfactor) {}
};

std::ostream& operator<<(std::ostream&, const MOBO&);

class RAM : public Part {
	int clk;	///Órajel
	int size;	///Memória
public:
	explicit RAM(String brand, String type, int price, int clk, int size) : Part(brand, type, price), clk(clk), size(size) {}
	explicit RAM(TempInput tmp) :Part(tmp.brand, tmp.type, tmp.price), clk(tmp.clk), size(tmp.size) {}
};

std::ostream& operator<<(std::ostream&, const RAM&);

class Case : public Part {
	String formfactor;	///Méret szabvány
public:
	explicit Case(String brand, String type, int price, String formfactor) : Part(brand, type, price), formfactor(formfactor) {}
	explicit Case(TempInput tmp) :Part(tmp.brand, tmp.type, tmp.price), formfactor(tmp.formfactor) {}
};

std::ostream& operator<<(std::ostream&, const Case&);

class PSU : public Part {
	String wattage;		///Teljesítmény
public:
	explicit PSU(String brand, String type, int price, String wattage) : Part(brand, type, price), wattage(wattage) {}
	explicit PSU(TempInput tmp) :Part(tmp.brand, tmp.type, tmp.price), wattage(tmp.wattage) {}
};

std::ostream& operator<<(std::ostream&, const PSU&);

class Storage : public Part {
protected:
	int size;			///Méret
	int readspeed;		///Olvasási sebesség
	int writespeed;		///Írási sebesség
public:
	explicit Storage(String brand, String type, int price, int size, int readspeed, int writespeed) : Part(brand, type, price),
		size(size), readspeed(readspeed), writespeed(writespeed) {}
};

class SSD : public Storage {
	String formfactor;	///Szabvány
	String flashtype;	///Flash csip típusa
public:
	explicit SSD(String brand, String type, int price, int size, int readspeed, int writespeed, String formfactor, String flashtype) :
		Storage(brand, type, price, size, readspeed, writespeed), formfactor(formfactor), flashtype(flashtype) {}
	explicit SSD(TempInput tmp) :Storage(tmp.brand, tmp.type, tmp.price, tmp.size, tmp.readspeed, tmp.writespeed), formfactor(tmp.formfactor), flashtype(tmp.flashtype) {}
};

std::ostream& operator<<(std::ostream&, const SSD&);

class HDD : public Storage {
	int rpm;	///Fordulatszám
public:
	explicit HDD(String brand, String type, int price, int size, int readspeed, int writespeed, int rpm) :
		Storage(brand, type, price, size, readspeed, writespeed), rpm(rpm) {}
	explicit HDD(TempInput tmp) :Storage(tmp.brand, tmp.type, tmp.price, tmp.size, tmp.readspeed, tmp.writespeed), rpm(tmp.rpm) {}
};

std::ostream& operator<<(std::ostream&, const HDD&);