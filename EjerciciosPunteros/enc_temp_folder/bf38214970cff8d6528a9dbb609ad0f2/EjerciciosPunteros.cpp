#include <iostream>

using namespace std;

void ej1()
{
	int x = 5, y = 12, z;
	int *p1, *p2, *p3;
	p1 = &x;
	p2 = &y;
	z = *p1 * *p2;
	p3 = &z;
	(*p3)++;
	p1 = p3;
	cout << *p1 << " " << *p2 << " " << *p3 << endl;
}

void ej2()
{
	int dato = 5;
	int *p1, p2;
	p1 = &dato;
	//p2 = p1;
	//cout << *p2;
}

void ej3()
{
	double d = 5.4, e = 1.2, f = 0.9;
	double *p1, *p2, *p3;
	p1 = &d;
	(*p1) = (*p1) + 3;
	p2 = &e;
	p3 = &f;
	(*p3) = (*p1) + (*p2);
	cout << *p1 << " " << *p2 << " " << *p3;
}

struct Registro
{
	string nombre;
	double sueldo;
	int edad;
};

void func(Registro* reg, double* irpf, int* edad)
{
	const double TIPO = 0.18;
	reg->edad++;
	*irpf = reg->sueldo * TIPO;
	*edad = reg->edad;
}

int main()
{
	Registro r1;
	r1.nombre = "Paco";
	r1.sueldo =  15000;
	r1.edad = 53;
	auto* pr = new Registro;

	// los registros r1 y *pr toman valor
	double cotiza = 0;
	int anyos = 0;
	double* p1 = &cotiza;
	int* p2 = &anyos;

	//func(r1, cotiza, años);
	func(pr, p1, p2);

	delete pr;
	delete p1;
	//delete p2;
	cout << r1.nombre << " " << r1.sueldo << " " << r1.edad << endl;
	//cout << *p1 << " " << *p2 << " " << endl;
	//cout << pr->nombre << " " << pr->sueldo << " " << pr->edad << endl;
}