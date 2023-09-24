#include <iostream>
#include <fstream>
#include "Date.cpp"
#include <windows.h>
#include <string>
#include <array>
#include <algorithm>

struct Coche 
{
    int id;
    int precio;
    std::string marca;
    std::string modelo;

    Coche(const int i, const int p, const std::string &ma, const std::string &mo) {
        id = i;
        precio = p;
        marca = ma;
        modelo = mo;
    }

    Coche() = default;
};

struct Alquiler
{
    int id;
    int dias;
    Date fecha;

    Alquiler(const int i, const int d, const Date &f)
    {
        id = i;
        dias = d;
        fecha = f;
    }

    Alquiler() = default;
};

struct ListaCoches
{
    int tam = 10;
    int num = 0;
    Coche* c = new Coche[tam];

    ListaCoches(const int t, const int n)
    {
        tam = t + 10;
        num = n;

        c = new Coche[tam];
    }

    ListaCoches() = default;
};

struct ListaAlquileres
{
    int tam = 10;
    int num = 0;
    Alquiler* a = new Alquiler[tam];

    ListaAlquileres(const int t, const int n)
    {
        tam = t + 10;
        num = n;

        a = new Alquiler[tam];
    }

    ListaAlquileres() = default;
};

bool leerModelos(ListaCoches &lc) 
{
    bool abierto = false;
    std::ifstream entrada("coches.txt");
    if (entrada.is_open())
    {
        abierto = true;
        int num = 0;
        entrada >> num;
        for (int i = 0; i < num; i++)
        {
            int id = 0;
            int precio = 0;
            std::string marca;
            std::string modelo;
            entrada >> id;
            entrada >> precio;
            entrada >> marca;
            entrada >> modelo;
            auto coche = Coche(id, precio, marca, modelo);
            lc.c[lc.num] = coche;
            //std::cout << "Coche " << i << ": " << lc.c[lc.num].id << " " << lc.c[lc.num].precio << " " << lc.c[lc.num].marca << " " << lc.c[lc.num].modelo << "\n";
            lc.num++;
        }
    }
    return abierto;
}

int leerAlquileres(ListaAlquileres &la)
{
    bool abierto = false;
    std::ifstream entrada("rent.txt");
    if (entrada.is_open())
    {
        abierto = true;
        int num = 0;
        entrada >> num;
        for (int i = 0; i < num; i++)
        {
            int id = 0;
            int dias = 0;
            Date fecha = Date();
            entrada >> id;
            entrada >> fecha;
            entrada >> dias;
            auto alquiler = Alquiler(id, dias, fecha);
            la.a[la.num] = alquiler;
            //std::cout << "Coche " << i << ": " << la.a[la.num].id << " " << la.a[la.num].dias << " " << la.a[la.num].fecha << "\n";
            la.num++;
        }
    }
    return abierto;
}


int ordenarAlquileres()
{
    return 0;
}

int buscarCoche(ListaCoches lc, int id)
{
    int ini = 0, n = lc.num -1;
    bool enc = false;
    int indiceEnc = -1;
    while (ini <= n && !enc) {
        int med = (ini + n) / 2;
        if (id < lc.c[med].id)
            n = med - 1;
        else if (id > lc.c[med].id)
            ini = med + 1;
        else
        {
            enc = true;
            indiceEnc = med;
        }
    }
    return indiceEnc;
}

int mostrarAlquileres(ListaCoches lc, ListaAlquileres la)
{
    int idBuscar = 0;
    for (int i = 0; i < la.num; i++)
    {
        idBuscar = buscarCoche(lc, la.a[i].id);
        if (idBuscar != -1)
            std::cout << la.a[i].fecha << " " << lc.c[idBuscar].marca << " " << lc.c[idBuscar].modelo << " " << la.a[i].dias << " día(s) por " << (la.a[i].dias * lc.c[idBuscar].precio) << " euros\n";
        else
            std::cout << la.a[i].fecha << " ERROR: Modelo inexistente\n";
    }
    return 0;
}

int main()
{
    auto lc = ListaCoches();
    auto la = ListaAlquileres();
    SetConsoleOutputCP(CP_UTF8);
    leerModelos(lc);
    leerAlquileres(la);
    //std::cout << buscarCoche(lc, 1620);
    mostrarAlquileres(lc, la);
}

