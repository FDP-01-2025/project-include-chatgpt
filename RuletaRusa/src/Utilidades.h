#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Jugador.h"
#include "TextoLento.h"
#include <cstdlib>
#include <iostream>

using namespace std;



void imprimirEstado(Jugador j1, Jugador j2) {
    textoLento("\033[1;97m\n=======================\n\033[0m");
    textoLento("\033[1;97m" + j1.nombre + " | Lives: " + to_string(j1.vidas) + " ❤️\n\033[0m");
    textoLento("\033[1;97m" + j2.nombre + " | Lives: " + to_string(j2.vidas) + " ❤️\n\033[0m");
    textoLento("\033[1;97m=======================\n\033[0m");
}


int girarTambor() {
    return rand() % 6;
}

bool disparar() {
    return rand() % 6 == 0;
}

void turnoJugador(Jugador &jugador, Jugador &oponente) {

    textoLento("\033[1;97m\nIt's " + jugador.nombre + "'s turn...\n\033[0m");
    textoLento("\033[1;97m1. Spin the chamber\n\033[0m");
    textoLento("\033[1;97m2. Shoot yourself\n\033[0m");
    if (jugador.corteDisponible) textoLento("\033[1;93m3. Use powered bullet (double damage)\n\033[0m");
    if (jugador.curacionDisponible) textoLento("\033[1;96m4. Use HEAL (recover +1 life)\n\033[0m");
    textoLento("\033[1;97mChoose an option: \033[0m");

    int opcion;
    cin >> opcion;

    switch(opcion) {
        case 1:
            textoLento("\033[1;97m🔄 You spun the chamber...\n\033[0m", 50);
            break;
        case 2:
            textoLento("\033[1;97m🔫 You pointed the gun and pulled the trigger...\n\033[0m", 60);
            if (disparar()) {
                textoLento("\033[1;31m💥 BANG! You lost a life.\033[0m\n", 90);
                jugador.vidas -= 1;
            } else {
                textoLento("\033[1;92m🫣 CLICK! No bullet came out.\033[0m\n", 80);
            }
            break;
        case 3:
            if (jugador.corteDisponible) {
                textoLento("\033[1;93m⚔️ You charged a powered bullet into the chamber. Damage will be doubled if the bullet fires.\033[0m\n", 50);
                if (disparar()) {
                    textoLento("\033[1;31m💥 BANG! You lost 2 lives.\033[0m\n", 90);
                    jugador.vidas -= 2;
                } else {
                    textoLento("\033[1;92m🫣 CLICK! You survived.\033[0m\n", 80);
                }
                jugador.corteDisponible = false;
            } else {
                textoLento("\033[1;90m❌ No SLASH available.\033[0m\n");
            }
            break;
        case 4:
            if (jugador.curacionDisponible) {
                textoLento("\033[1;96m💊 You used HEAL. You regained 1 life.\033[0m\n", 60);
                jugador.vidas += 1;
                jugador.curacionDisponible = false;
            } else {
                textoLento("\033[1;90m❌ You've already used your heal.\033[0m\n");
            }
            break;
        default:
            textoLento("\033[1;90m❌ Invalid option.\033[0m\n", 70);
    }

     

}

bool estaVivo(Jugador j) {
    return j.vidas > 0;
}

#endif