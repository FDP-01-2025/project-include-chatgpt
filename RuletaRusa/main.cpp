#include <iostream>
#include <cstdlib>
#include <ctime>
#include "src/Jugador.h"
#include "src/Utilidades.h"
#include "src/Registro.h"
#include "src/TextoLento.h"

using namespace std;

//--------------Programador 2------------------------------.
// Configuracion del tambor(variables globales).
int TAMANO_BARRIL = 6;    // Tamaño del barril de la pistola.
int VACIO = 0;            // Valor que representa cuando no hay bala presente en la recamara.
int BALA = 1;             // Valor que representa cuando hay bala presente en la recamara.

int barril[6];            // Arreglo que representa el tambor(6 disparos).
int posicionActual = 0;   // Posición actual del tambor (camara alineada al tambor).

//  FUNCIÓN 1: Verifica si hay al menos una bala en el barril
bool hayBalaEnBarril() {
    bool encontrada = false;
    for (int i = 0; i < TAMANO_BARRIL; i++) {
        if (barril[i] == BALA) {
            encontrada = true; 
        }
    }

    if (encontrada) {
        return true; //Encontro una bala 
    } else {
        return false; 
    }
}


// FUNCIÓN 2: Recarga la pistola solo si está vacía.
void recargarSiVacio() {
    if (hayBalaEnBarril()) return;  // Si ya hay bala, no hace nada.

    // Vacía todas las cámaras
    for (int i = 0; i < TAMANO_BARRIL; i++) {
        barril[i] = VACIO;
    }

    // Coloca una única bala en una posición aleatoria
    int pos = rand() % TAMANO_BARRIL;
    barril[pos] = BALA;
}

// FUNCIÓN 3: Gira el tambor y dispara
int girarYDisparar() {
    posicionActual = rand() % TAMANO_BARRIL;        // Gira y elige un espacio de la recamara del 1 al 6 
    int bala = barril[posicionActual];              // Lee si hay bala
    barril[posicionActual] = VACIO;                 // Cámara disparada se vacía
    posicionActual = (posicionActual + 1) % TAMANO_BARRIL;  // Avanza cámara (opcional)
    return bala;  // 1 = BANG (hubo bala), 0 = CLICK (vacío)
}
//------------------------Programador 2------------------------.

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