#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Jugador.h"
#include "TextoLento.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void imprimirEstado(Player j1, Player j2) {
    slowText("\033[1;97m\n=======================\n\033[0m");
    slowText("\033[1;97m" + j1.name + " | Lives: " + to_string(j1.lifes) + " ❤️\n\033[0m");
    slowText("\033[1;97m" + j2.name + " | Lives: " + to_string(j2.lifes) + " ❤️\n\033[0m");
    slowText("\033[1;97m=======================\n\033[0m");
}

int girarTambor() {
    return rand() % 6;
}

bool shot() {
    return rand() % 6 == 0;
}

void playerTurn(Player &jugador, Player &oponente) {
    slowText("\033[1;97m\nIt's " + jugador.name + "'s turn...\n\033[0m");
    slowText("\033[1;97m1. Spin the chamber\n\033[0m");
    slowText("\033[1;97m2. Shoot yourself\n\033[0m");
    if (jugador.poweredBullet) slowText("\033[1;93m3. Use powered bullet (double damage)\n\033[0m");
    if (jugador.healAvaible) slowText("\033[1;96m4. Use HEAL (recover +1 life)\n\033[0m");
    slowText("\033[1;97mChoose an option: \033[0m");

    int opcion;
    cin >> opcion;

    switch(opcion) {
        case 1:
            slowText("\033[1;97m🔄 You spin the chamber...\n\033[0m", 50);
            break;
        case 2:
            slowText("\033[1;97m🔫 You pointed the gun and pulled the trigger...\n\033[0m", 60);
            if (shot()) {
                slowText("\033[1;31m💥 BANG! You lost a life.\033[0m\n", 90);
                jugador.lifes -= 1;
            } else {
                slowText("\033[1;92m🫣 CLICK! No bullet came out.\033[0m\n", 80);
            }
            break;
        case 3:
            if (jugador.poweredBullet) {
                slowText("\033[1;93m⚔️ You charged a powered bullet into the chamber. Damage will be doubled if the bullet fires.\033[0m\n", 50);
                if (shot()) {
                    slowText("\033[1;31m💥 BANG! You lost 2 lives.\033[0m\n", 90);
                    jugador.lifes -= 2;
                } else {
                    slowText("\033[1;92m🫣 CLICK! You survived.\033[0m\n", 80);
                }
                jugador.poweredBullet = false;
            } else {
                slowText("\033[1;90m❌ No SLASH available.\033[0m\n");
            }
            break;
        case 4:
            if (jugador.healAvaible) {
                slowText("\033[1;96m💊 You used HEAL. You regained 1 life.\033[0m\n", 60);
                jugador.lifes += 1;
                jugador.healAvaible = false;
            } else {
                slowText("\033[1;90m❌ You've already used your heal.\033[0m\n");
            }
            break;
        default:
            slowText("\033[1;90m❌ Invalid option.\033[0m\n", 70);
    }
}

bool estaVivo(Player j) {
    return j.lifes > 0;
}

#endif