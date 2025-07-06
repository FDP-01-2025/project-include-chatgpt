#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> // Agregado para activar UTF-8 en consola (leer emojis)
#include "src/Jugador.h"
#include "src/Utilidades.h"
#include "src/Registro.h"
#include "src/TextoLento.h"

using namespace std;

//--------------Programador 2------------------------------
int chamber_capacity = 6;
int empty = 0;
int bullet = 1;

int chamber[6];
int current_position = 0;

bool bulletinchamber() {
    bool found = false;
    for (int i = 0; i < chamber_capacity; i++) {
        if (chamber[i] == bullet) {
            found = true; 
        }
    }

    return found;
}

void reloadifempty() {
    if (bulletinchamber()) return;

    for (int i = 0; i < chamber_capacity; i++) {
        chamber[i] = empty;
    }

    int pos = rand() % chamber_capacity;
    chamber[pos] = bullet;
}

int girarYDisparar() {
    current_position = rand() % chamber_capacity;
    int bala = chamber[current_position];
    chamber[current_position] = empty;
    current_position = (current_position + 1) % chamber_capacity;
    return bala;
}
//------------------------Programador 2------------------------

int main() {
    SetConsoleOutputCP(CP_UTF8); // ✅ Activa emojis en toda la consola

    srand(time(0));
    Jugador player1, player2;
    int mode;

    textoLento("🎲 Welcome to Rusian roulette 🎲\n");
    textoLento("1. 2 Players\n");
    textoLento("2. 1 Player vs CPU\n");
    textoLento("Select your game mode: ");
    cin >> mode;

    if (mode == 1) {
        cout << "Enter player 1 name: ";
        cin >> player1.nombre;
        cout << "Enter player 2 name: ";
        cin >> player2.nombre;
    } else {
        cout << "Player name: ";
        cin >> player1.nombre;
        player2.nombre = "CPU";
    }

    while (estaVivo(player1) && estaVivo(player2)) {
        imprimirEstado(player1, player2);
        turnoJugador(player1, player2);
        if (!estaVivo(player1)) break;

        imprimirEstado(player1, player2);
        if (player2.nombre == "CPU") {
            cout << "\nCPU turn...\n";
            if (disparar()) {
                cout << " CPU pulled the trigger...AND GOT SHOT!\n";
                player2.vidas -= 1;
            } else {
                cout << " CPU pulled the trigger...nothing happens.\n";
            }
        } else {
            turnoJugador(player2, player1);
        }
    }

    textoLento("\n🎉 GAME OVER 🎉\n");
    string ganador = estaVivo(player1) ? player1.nombre : player2.nombre;
    textoLento(ganador + " WINS\n");

    registrarVictoria(ganador);

    return 0;
}
