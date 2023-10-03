#include "ListaCoches.h"
#include "checkML.h"
#include <fstream>;

ListaCoches::ListaCoches(int tam, int num, Coche* c) : tam(tam), num(num), c(c) {}

bool ListaCoches::leer(std::string archivo)
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
            //ListaCoches::c[ListaCoches::num] = coche; 
            //ListaCoches::num++;
        }
    }
    return entrada.is_open();
}
