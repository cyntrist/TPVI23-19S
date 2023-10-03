// David Canelada Velasco
// Cynthia Tristán Álvarez

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
#include "ListaAlquileres.h"

using namespace std;

int main()
{
    Coche c = Coche(1, 5, "sa", "asdc");
    Coche p = Coche(1, 5, "sa", "asdc");

    Date asd = Date(1, 1, 2020);
    Date bdg = Date(1, 2, 2020);

    Alquiler a = Alquiler(1, 2, asd);
    Alquiler b = Alquiler(1, 2, bdg);

    if (a < b)
        std::cout << c.GetPrecio();
}
