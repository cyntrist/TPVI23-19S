#pragma once
#include "Alquiler.h"
#include "ListaCoches.h"
//#include "checkML.h"

class ListaAlquileres
{
	int tam;
	int num;
	Alquiler* a = new Alquiler[tam];
public:
	ListaAlquileres(int tam);
	Alquiler GetAlquiler(int position);
	void addRent(const Alquiler& alquiler) {
		a[num] = alquiler;
		num++;
	}
	bool read(const std::string& archivo);
	void show(ListaCoches &lc);
	void ordena();

};

