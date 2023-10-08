#include "Coche.h"
//#include "checkML.h" 

Coche::Coche() : id(0), precio(0), marca(""), modelo("") {}

Coche::Coche(int id, int precio, std::string marca, std::string modelo) : id(id), precio(precio), marca(marca), modelo(modelo) {}

int Coche::GetId() { return id; }

int Coche::GetPrecio() { return precio; }

std::string Coche::GetMarca() { return marca; }

std::string Coche::GetModelo() { return modelo; }

//bool Coche::operator==(const Coche& other) const { return id = other.id; } //me da error ay