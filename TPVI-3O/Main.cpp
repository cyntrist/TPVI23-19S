// Cynthia Tristán Álvarez
// David Canelada Velasco

#include <iostream>
#include <fstream>
#include "checkML.h"
#include "Date.h"
#include <windows.h>
#include <string>
#include <algorithm>

#include "Coche.h"
#include "ListaCoches.h"
#include "Alquiler.h"
#include "Date.h"
#include "ListaAlquileres.h"

using namespace std;

void showOptions()
{
    cout << "0. Salir" << endl
    << "1. Mostrar lista de coches." << endl
    << "2. Mostrar lista de alquileres." << endl
	<< "3. Añadir nuevo coche." << endl
	<< "4. Añadir nuevo alquiler." << endl;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
	//_crtBreakAlloc = 206; // memory leak debug

    /*
    auto c = Coche(1, 5, "sa", "asdc");
    auto p = Coche(1, 5, "sa", "asdc");

    auto asd = Date(1, 1, 2020);
    auto bdg = Date(1, 2, 2020);

    auto a = Alquiler(1, 2, asd);
    auto b = Alquiler(1, 2, bdg);

    auto la = ListaAlquileres();

	la.LeerAlquileres("rent.txt");
    std::cout << la.GetAlquiler(0).GetFecha();
    if (a < b)
		std::cout << c.GetPrecio();
	*/
    auto lc = ListaCoches(15);
    lc.read("coches.txt");

	int opcion = -1;
	showOptions();
    while (opcion != 0)
    {
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            lc.show();
            break;
        case 2:
            // ...
            break;
        case 3:
	        {
        		if (lc.getNum() < lc.getTam())
        		{
        			int id, precio;
		            std::string marca, modelo;

                    id = 1325; 
                    while (lc.search(id) != -1)  // ids únicos
                        id++;

		            cout << "¿Precio?" << endl;
		            cin >> precio;
		            cout << "¿Marca?" << endl;
		            cin >> marca;
		            cout << "¿Modelo?" << endl;
		            cin >> modelo; 

		            auto coche = Coche(id, precio, marca, modelo);
		            lc.addCar(coche);
                    sort(lc.getCars(), lc.getCars() + lc.getNum());
        		}
                else
                    cout << "No caben más coches." << endl;
	        }
            break;
        case 4:
            // ...
            // la.add...
            break;
        default: 
            break;
        }
     }

	lc.deleteCars();
}
