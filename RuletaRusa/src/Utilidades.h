#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Jugador.h"
#include "TextoLento.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void imprimirEstado(Jugador j1, Jugador j2) {
    textoLento("\033[1;97m\n=======================\n\033[0m");
    textoLento("\033[1;97m" + j1.nombre + " | Vidas: " + to_string(j1.vidas) + " ❤️\n\033[0m");
    textoLento("\033[1;97m" + j2.nombre + " | Vidas: " + to_string(j2.vidas) + " ❤️\n\033[0m");
    textoLento("\033[1;97m=======================\n\033[0m");
}

int girarTambor() {
    return rand() % 6;
}

bool disparar() {
    return rand() % 6 == 0;
}

void turnoJugador(Jugador &jugador, Jugador &oponente) {
    textoLento("\033[1;97m\nEs el turno de " + jugador.nombre + "...\n\033[0m");
    textoLento("\033[1;97m1. Girar recámara\n\033[0m");
    textoLento("\033[1;97m2. Dispararte\n\033[0m");
    if (jugador.corteDisponible) textoLento("\033[1;93m3. Usar CORTE (doble daño)\n\033[0m");
    if (jugador.curacionDisponible) textoLento("\033[1;96m4. Usar CURACIÓN (+1 vida)\n\033[0m");
    textoLento("\033[1;97mElige una opción: \033[0m");

    int opcion;
    cin >> opcion;

    switch(opcion) {
        case 1:
            textoLento("\033[1;97m🔄 Giraste la recámara...\n\033[0m", 50);
            break;
        case 2:
            textoLento("\033[1;97m🔫 Te apuntaste y jalaste el gatillo...\n\033[0m", 60);
            if (disparar()) {
                textoLento("\033[1;31m💥 BANG! Perdiste una vida.\033[0m\n", 90);
                jugador.vidas -= 1;
            } else {
                textoLento("\033[1;92m🫣 CLICK! No salió la bala.\033[0m\n", 80);
            }
            break;
        case 3:
            if (jugador.corteDisponible) {
                textoLento("\033[1;93m⚔️ Usaste CORTE. El daño será doble si te toca la bala.\033[0m\n", 50);
                if (disparar()) {
                    textoLento("\033[1;31m💥 BANG! Perdiste 2 vidas.\033[0m\n", 90);
                    jugador.vidas -= 2;
                } else {
                    textoLento("\033[1;92m🫣 CLICK! Te salvaste.\033[0m\n", 80);
                }
                jugador.corteDisponible = false;
            } else {
                textoLento("\033[1;90m❌ No tienes CORTE disponible.\033[0m\n");
            }
            break;
        case 4:
            if (jugador.curacionDisponible) {
                textoLento("\033[1;96m💊 Usaste CURACIÓN. Recuperaste 1 vida.\033[0m\n", 60);
                jugador.vidas += 1;
                jugador.curacionDisponible = false;
            } else {
                textoLento("\033[1;90m❌ Ya usaste tu curación.\033[0m\n");
            }
            break;
        default:
            textoLento("\033[1;90m❌ Opción inválida.\033[0m\n", 70);
    }
}

bool estaVivo(Jugador j) {
    return j.vidas > 0;
}

#endif