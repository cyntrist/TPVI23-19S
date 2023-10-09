#include "Alquiler.h"
#include "checkML.h"
Alquiler::Alquiler() : id(), dias(), fecha(){}

Alquiler::Alquiler(int id, int dias, Date fecha) : id(id), dias(dias), fecha(fecha){}

int Alquiler::GetId() {
	return id;
}

int Alquiler::GetDias() {
	return dias;
};

Date Alquiler::GetFecha() {
	return fecha;
}

bool Alquiler::operator<(const Alquiler& alquiler) const {
	return alquiler.fecha < fecha;
}