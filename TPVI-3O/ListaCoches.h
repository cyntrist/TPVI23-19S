#pragma once
//#include "checkML.h" // me da error de compilacion si lo pongo en archivos distintos al main, quizá porque no hay que ponerlo en main
#include "Coche.h"

class ListaCoches
{
	int tam;
	int num;
	Coche* c;
	Coche** c2;

public:
	// getters
	int getTam() { return tam; }
	int getNum() { return num; }
	Coche* getCars() { return c; }

	// setters
	void setTam(const int v) { tam = v; }
	void setNum(const int v) { num = v; }
	void setCars(Coche* v) { c = v; }

	void addNum() { num++; }
	void addCar(const Coche& v) { c[num] = v; num++; }
	Coche getCar(const int pos) { return c[pos]; }

	// constructores
	ListaCoches() = default;
	ListaCoches(int tam);

	// métodos
	bool read(const std::string& archivo);
	int search(int id);
	void show();

	// delete
	void deleteCars(); 
};

