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
	ListaCoches lc = ListaCoches();
	lc.leer("coches.txt");
}
