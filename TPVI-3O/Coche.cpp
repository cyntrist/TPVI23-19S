#include "Coche.h"
#include "checkML.h"

Coche::Coche() : id(), precio(), marca(), modelo() {}

Coche::Coche(int id, int precio, std::string marca, std::string modelo) : id(id), precio(precio), marca(marca), modelo(modelo) {}