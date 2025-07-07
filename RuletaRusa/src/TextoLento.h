#ifndef TEXTOLENTO_H
#define TEXTOLENTO_H

#include <iostream>
#include <string>
#include <windows.h>  // Para Sleep()

using namespace std;

// Muestra texto con efecto de tipeo lento
void textoLento(const string& texto, int velocidad = 10) {
    for (char c : texto) {
        cout << c << flush;
        Sleep(velocidad);  // Milisegundos en Windows
    }
}

#endif
