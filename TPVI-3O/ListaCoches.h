#pragma once
#include "Coche.h"

class ListaCoches
{
	int tam;
	int num;
	Coche* c = new Coche[tam];

public:
	int getTam() { return tam; }
	int getNum() { return num; }
	// getCar
	void setTam(const int v) { tam = v; }
	void setNum(const int v) { num = v; }
	void addNum() { num++; }
	void addCar(const Coche& v) { c[num] = v; }

	ListaCoches() = default;
	ListaCoches(int tam);
	//ListaCoches(int tam, int num, Coche* c);
	bool leer(const std::string& archivo);

};

