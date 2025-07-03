#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>

using namespace std;

struct Jugador {
    string nombre;
    int vidas = 3;
    bool corteDisponible = true;
    bool curacionDisponible = true;
};

#endif