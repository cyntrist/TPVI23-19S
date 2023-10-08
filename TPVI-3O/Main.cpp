// Cynthia Tristán Álvarez
// David Canelada Velasco

#include <iostream>
#include <fstream>
#include "checkML.h"
#include "Date.h"
#include <windows.h>
#include <string>
#include <array>
#include <algorithm>

#include "Coche.h"
#include "ListaCoches.h"
#include "Alquiler.h"
#include "Date.h"
#include "ListaAlquileres.h"

using namespace std;

int main()
{
    auto c = Coche(1, 5, "sa", "asdc");
    auto p = Coche(1, 5, "sa", "asdc");

    auto asd = Date(1, 1, 2020);
    auto bdg = Date(1, 2, 2020);

    auto a = Alquiler(1, 2, asd);
    auto b = Alquiler(1, 2, bdg);

    auto la = ListaAlquileres();
    auto lc = ListaCoches(10);
    lc.leer("coches.txt");
    //la.LeerAlquileres("rent.txt");
    //std::cout << la.GetAlquiler(0).GetFecha();
    //if (a < b)
    //    std::cout << c.GetPrecio();
}
