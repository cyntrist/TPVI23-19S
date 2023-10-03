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

using namespace std;

int main()
{
    Coche c = Coche(1, 5, "sa", "asdc");
    Coche p = Coche(1, 5, "sa", "asdc");

    std::cout << c.GetPrecio();
}
