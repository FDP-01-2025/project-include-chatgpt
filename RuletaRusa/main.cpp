#include <iostream>
#include <cstdlib>
#include <ctime>
#include "src/Jugador.h"
#include "src/Utilidades.h"
#include "src/Registro.h"
#include "src/TextoLento.h"

using namespace std;

int main() {
    srand(time(0));
    Jugador jugador1, jugador2;
    int modo;

    textoLento("🎲 Bienvenido a la Ruleta Rusa 🎲\n");
    textoLento("1. 2 Jugadores\n");
    textoLento("2. 1 Jugador vs CPU\n");
    textoLento("Selecciona modo de juego: ");
    cin >> modo;

    if (modo == 1) {
        cout << "Nombre del Jugador 1: ";
        cin >> jugador1.nombre;
        cout << "Nombre del Jugador 2: ";
        cin >> jugador2.nombre;
    } else {
        cout << "Nombre del Jugador: ";
        cin >> jugador1.nombre;
        jugador2.nombre = "CPU";
    }

    while (estaVivo(jugador1) && estaVivo(jugador2)) {
        imprimirEstado(jugador1, jugador2);
        turnoJugador(jugador1, jugador2);
        if (!estaVivo(jugador1)) break;

        imprimirEstado(jugador1, jugador2);
        if (jugador2.nombre == "CPU") {
            cout << "\nTurno de la CPU...\n";
            if (disparar()) {
                cout << "💻 CPU se disparó... ¡y se dio!\n";
                jugador2.vidas -= 1;
            } else {
                cout << "💻 CPU jaló el gatillo... nada pasó.\n";
            }
        } else {
            turnoJugador(jugador2, jugador1);
        }
    }

    textoLento("\n🎉 ¡FIN DEL JUEGO! 🎉\n");
    string ganador = estaVivo(jugador1) ? jugador1.nombre : jugador2.nombre;
    textoLento(ganador + " gana!\n");

    registrarVictoria(ganador);

    return 0;
}