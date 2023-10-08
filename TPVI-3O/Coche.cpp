#include "Coche.h"
//#include "checkML.h" 

Coche::Coche() : id(0), precio(0), marca(""), modelo("") {}

Coche::Coche(const int id, const int precio, const std::string marca, const std::string modelo) : id(id), precio(precio), marca(marca), modelo(modelo) {}