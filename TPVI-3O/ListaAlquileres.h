#pragma once
#include "Alquiler.h"
//#include "checkML.h"

class ListaAlquileres
{
private:
	int tam;
	int num;
	Alquiler* a = new Alquiler[tam];
public:
	ListaAlquileres();
	ListaAlquileres(int tam, int num, Alquiler* lista);
	Alquiler GetAlquiler(int position);
	void AddAlquiler(int pos, Alquiler alquiler) {
		a[pos] = alquiler;
	}
	bool LeerAlquileres(std::string archivo);

};

