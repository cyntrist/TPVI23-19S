// Cynthia Tristán Álvarez
// David Canelada Velasco
#pragma once
#include "Date.h"

class Alquiler
{
private:
    int id;
    int dias;
    Date fecha;
public:
    Alquiler();
    Alquiler(int id, int dias, Date fecha);
    int GetId();
    int GetDias();
    Date GetFecha();
    bool operator< (const Alquiler& alquiler) const;
};

