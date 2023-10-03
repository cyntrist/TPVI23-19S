#pragma once
#include "Coche.h"

class ListaCoches
{
public:
	int tam;
	int num;
	Coche* c = new Coche[tam];

public:
	ListaCoches() = default;
	ListaCoches(int tam, int num, Coche* c);
	bool leer(std::string archivo);
};

