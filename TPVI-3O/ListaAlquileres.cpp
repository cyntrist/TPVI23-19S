#include "ListaAlquileres.h"
#include "checkML.h"
#include <string>
#include <fstream>
ListaAlquileres::ListaAlquileres() : tam(), num(), a(){}
ListaAlquileres::ListaAlquileres(int tam, int num, Alquiler* lista) : tam(tam), num(num), a(lista){}

Alquiler ListaAlquileres::GetAlquiler(int position) {
    return a[position];
}

bool ListaAlquileres::LeerAlquileres(std::string archivo)
{
    bool abierto = false;
    std::ifstream entrada(archivo);
    if (entrada.is_open())
    {
        abierto = true;
        int num = 0;
        entrada >> num;
        for (int i = 0; i < num; i++)
        {
            int id = 0;
            int dias = 0;
            auto fecha = Date();
            entrada >> id;
            entrada >> fecha;
            entrada >> dias;
            const auto alquiler = Alquiler(id, dias, fecha);
            AddAlquiler(num, alquiler);
            //a[num] = alquiler; //peta aqui
            //std::cout << "Coche " << i << ": " << la.a[la.num].id << " " << la.a[la.num].dias << " " << la.a[la.num].fecha << "\n";
            num++;
        }
    }
    return abierto;
}

