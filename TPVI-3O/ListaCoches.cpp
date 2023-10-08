#include "ListaCoches.h"
//#include "checkML.h"
#include <fstream>

//ListaCoches::ListaCoches(int tam, int num, Coche* c) : tam(tam), num(num), c(c) {}

ListaCoches::ListaCoches(int t)
{
	tam = t;
    num = 0;
    auto c = new Coche[tam];
}

void ListaCoches::deleteCars() { delete[] c; }

bool ListaCoches::read(const std::string& archivo)
{
    std::ifstream entrada(archivo);
    if (entrada.is_open())
    {
        int cant = 0;
        entrada >> cant;
        for (int i = 0; i < cant; i++)
        {
            int id;
            int precio;
            std::string marca;
            std::string modelo;

            entrada >> id;
            entrada >> precio;
            entrada >> marca;
            entrada >> modelo;

            const auto coche = Coche(id, precio, marca, modelo);
            addCar(coche);
            addNum();
        }
    }
    return entrada.is_open();
}

int ListaCoches::search(const int id)
{
	int ini = 0, n = getNum() - 1;
    bool enc = false;
    int indiceEnc =  -1;
    while (ini <= n && !enc) {
        const int med = (ini + n) / 2;
        if (id < getCar(med).GetId())
            n = med - 1;
        else if (id > getCar(med).GetId())
            ini = med + 1;
        else
        {
            enc = true;
            indiceEnc = med;
        }
    }
    return indiceEnc;
}