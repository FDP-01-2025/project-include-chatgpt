#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Jugador.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void imprimirEstado(Jugador j1, Jugador j2) {
    cout << "\n=======================\n";
    cout << j1.nombre << " | Vidas: " << j1.vidas << " ❤️\n";
    cout << j2.nombre << " | Vidas: " << j2.vidas << " ❤️\n";
    cout << "=======================\n";
}

int girarTambor() {
    return rand() % 6;
}

bool disparar() {
    return rand() % 6 == 0;
}

void turnoJugador(Jugador &jugador, Jugador &oponente) {
    cout << "\nEs el turno de " << jugador.nombre << "...\n";
    cout << "1. Girar recámara\n";
    cout << "2. Dispararte\n";
    if (jugador.corteDisponible) cout << "3. Usar CORTE (doble daño)\n";
    if (jugador.curacionDisponible) cout << "4. Usar CURACIÓN (+1 vida)\n";
    cout << "Elige una opción: ";

    int opcion;
    cin >> opcion;

    switch(opcion) {
        case 1:
            cout << "🔄 Giraste la recámara...\n";
            break;
        case 2:
            cout << "🔫 Te apuntaste y jalaste el gatillo...\n";
            if (disparar()) {
                cout << "💥 BANG! Perdiste una vida.\n";
                jugador.vidas -= 1;
            } else {
                cout << "🫣 CLICK! No salió la bala.\n";
            }
            break;
        case 3:
            if (jugador.corteDisponible) {
                cout << "⚔️ Usaste CORTE. El daño será doble si te toca la bala.\n";
                if (disparar()) {
                    cout << "💥 BANG! Perdiste 2 vidas.\n";
                    jugador.vidas -= 2;
                } else {
                    cout << "🫣 CLICK! Te salvaste.\n";
                }
                jugador.corteDisponible = false;
            } else {
                cout << "❌ No tienes CORTE disponible.\n";
            }
            break;
        case 4:
            if (jugador.curacionDisponible) {
                cout << "💊 Usaste CURACIÓN. Recuperaste 1 vida.\n";
                jugador.vidas += 1;
                jugador.curacionDisponible = false;
            } else {
                cout << "❌ Ya usaste tu curación.\n";
            }
            break;
        default:
            cout << "Opción inválida.\n";
    }
}

bool estaVivo(Jugador j) {
    return j.vidas > 0;
}

#endif