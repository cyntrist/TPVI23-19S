#include <iostream>
#include <fstream>
#include "Date.h"
#include <windows.h>
#include <string>

struct ListaCoches
{
    int tam;
    int num;
    Coche* c = new Coche[tam]
};


struct Coche 
{
    int id;
    int precio;
    std::string marca;
    std::string modelo;

    Coche(int i, int p, std::string ma, std::string mo) {
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

    Alquiler(int i, int d, Date f)
    {
        id = i;
        dias = d;
        fecha = f;
    }

    Alquiler() = default;
};

bool leerModelos() 
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
            std::cout << "Coche " << i << ": " << id << " " << precio << " " << marca << " " << modelo << "\n";
            Coche c = Coche(id, precio, marca, modelo);
        }
    }
    return abierto;
}

int leerAlquileres()
{
    bool abierto = false;
    std::ifstream entrada("rent.txt");
    if (entrada.is_open())
    {
        abierto = true;
        //...
    }
    return abierto;
}

int ordenarAlquileres()
{
    return 0;
}

int buscarCoche()
{
    return 0;
}

int mostrarAlquileres()
{
    return 0;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "Hello World!\n";
    leerModelos();
}

