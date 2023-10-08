#pragma once
//#include "checkML.h" // me da error de compilacion si lo pongo en archivos distintos al main, quizá porque no hay que ponerlo en main
#include "Coche.h"

class ListaCoches
{
	int tam;
	int num;
	Coche* c;
	Coche** c2; // array dinámico de punteros?

public:
	// constructores
	ListaCoches() = default;
	ListaCoches(int tam);

	// getters
	int getTam() { return tam; }
	int getNum() { return num; }
	Coche* getCars() { return c; }
	Coche getCar(const int pos) { return c[pos]; }

	// setters
	void setTam(const int v) { tam = v; }
	void setNum(const int v) { num = v; }
	void setCars(Coche* v) { c = v; }

	void addNum() { num++; }
	void addCar(const Coche& v) { c[num] = v; num++; }

	// delete
	void deleteCars() { delete[] c; }

	// métodos
	bool read(const std::string& archivo);
	int search(int id);
	void show();

	// c2
	Coche** getCars2() { return c2; }
	void addCar2(Coche* v) { c2[num] = v; num++; }
	void setCars2(Coche** v) { c2 = v; }
	Coche* getCar2 (const int pos) { return c2[pos]; }
	void deleteCars2() { delete[] c2; }
};

