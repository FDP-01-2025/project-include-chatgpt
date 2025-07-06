#ifndef REGISTRO_H
#define REGISTRO_H

#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

// Verifica si el usuario ya existe
bool usuarioExiste(const string& nombreBuscado) {
    ifstream entrada("registro_victorias.txt");
    string nombre, etiqueta;
    int victorias;

    while (entrada >> nombre >> etiqueta >> victorias) {
        if (nombre == nombreBuscado) {
            return true;
        }
    }

    return false;
}

// Crea un nuevo usuario con 0 victorias
void crearUsuario(const string& nombreNuevo) {
    ofstream salida("registro_victorias.txt", ios::app);
    salida << nombreNuevo << " victorias: 0" << endl;
}

// Suma +1 victoria al jugador, o lo crea si no existía
void registrarVictoria(const string& nombreGanador) {
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
