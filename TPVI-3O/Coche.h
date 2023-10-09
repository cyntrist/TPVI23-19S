// Cynthia Tristán Álvarez
// David Canelada Velasco
#pragma once
#include <string>

class Coche
{
private:
	int id;
	int precio;
	std::string marca;
	std::string modelo;
 
public:
	Coche();
	Coche(int id, int precio, std::string marca, std::string modelo);
	int getId() { return id; };
	int getPrecio() { return precio; };
	std::string getMarca() { return marca; }
	std::string getModelo() { return modelo; };
	friend bool operator<(const Coche& izdo, const Coche& dcho) { return izdo.id < dcho.id; }
};