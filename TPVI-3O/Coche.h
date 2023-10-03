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
	int GetId();
	int GetPrecio();
	std::string GetMarca();
	std::string GetModelo();
	//bool operator==(const Coche& other) const;
};