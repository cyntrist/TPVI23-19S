#include "ListaAlquileres.h"
//#include "checkML.h"
#include <string>
#include <fstream>
#include <algorithm>

ListaAlquileres::ListaAlquileres(int size)
{
    tam = size;
    num = 0;
    a = new Alquiler[tam];
}

Alquiler ListaAlquileres::GetAlquiler(int position) {
    return a[position];
}

bool ListaAlquileres::read(const std::string& archivo)
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
            auto alquiler = Alquiler(id, dias, fecha);

            addRent(alquiler);
            //a[num] = alquiler; //peta aqui
            //std::cout << "Coche " << i << ": " << a.a[a.num].id << " " << a.a[a.num].dias << " " << a.a[a.num].fecha << "\n";
        }
    }
    return abierto;
}

void ListaAlquileres::show(ListaCoches &lc) {
    for (int i = 0; i < num; i++) {
        Alquiler auxA = GetAlquiler(i);
        std::cout << auxA.GetFecha() << " ";
        Coche auxC = lc.getCar(lc.search(auxA.GetId()));
        std::cout << auxC.getId()
            << auxC.getMarca()
            << " "
            << auxC.getModelo()
            << " por "
            << auxC.getPrecio()
            << " €/día "
            << auxA.GetDias()
            << " día(s) por "
            << auxC.getPrecio() * auxA.GetDias()
            << " euros\n";

    }
}

void ListaAlquileres::ordena() {
    //std::sort(a, a, a + tam);
}
