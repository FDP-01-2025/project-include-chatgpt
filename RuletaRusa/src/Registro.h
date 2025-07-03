#ifndef REGISTRO_H
#define REGISTRO_H

#include <fstream>
#include <string>

using namespace std;

void registrarVictoria(string nombreGanador) {
    ifstream entrada("registro_victorias.txt");
    ofstream salidaTemp("temp.txt");
    string nombre, etiqueta;
    int victorias;
    bool encontrado = false;

    while (entrada >> nombre >> etiqueta >> victorias) {
        if (nombre == nombreGanador) {
            victorias++;
            encontrado = true;
        }
        salidaTemp << nombre << " victorias: " << victorias << endl;
    }

    entrada.close();

    if (!encontrado) {
        salidaTemp << nombreGanador << " victorias: 1" << endl;
    }

    salidaTemp.close();
    remove("registro_victorias.txt");
    rename("temp.txt", "registro_victorias.txt");
}

#endif