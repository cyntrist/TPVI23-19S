#ifndef COCHE_H_
#define COCHE_H_
//#pragma once
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
	int GetPrecio();
};
#endif