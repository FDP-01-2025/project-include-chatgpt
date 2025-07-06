#include <iostream>
#include <cstdlib> //Para generar posiciones aleatorias del barril y para inicializar el generador de numeros aleatorios.
#include <ctime>  // Obtener la hora actual para crear una semilla variable y que los números aleatorios no se repitan entre ejecuciones.
#include <windows.h> // Para activar soporte de emojis con UTF-8
#include "src/Jugador.h"
#include "src/Utilidades.h"
#include "src/Registro.h" //  Funciones para registrar jugadores y sus victorias
#include "src/TextoLento.h"
#include <windows.h> //Biblioteca para reproducir sonidos dentro del codigo.
#include <mmsystem.h>

using namespace std;

//--------------Programador 2------------------------------.
// Configuracion del tambor(variables globales).
int chamber_capacity = 6;    // Tamaño del barril de la pistola.
int blank = 0;               // CAMBIO: antes se llamaba 'empty'
int bullet = 1;             // Valor que representa cuando hay bala presente en la recamara.

int chamber[6];            // Arreglo que representa el tambor(6 disparos).
int current_position = 0;   // Posición actual del tambor (camara alineada al tambor).

//  FUNCIÓN 1: Verifica si hay al menos una bala en el barril
bool bulletinchamber() {
    bool found = false;
    for (int i = 0; i < chamber_capacity; i++) {
        if (chamber[i] == bullet) {
            found = true; 
        }
    }

    if (found) {
        return true; //Encontro una bala 
    } else {
        return false; 
    }
}


// FUNCIÓN 2: Recarga la pistola solo si está vacía.
void reloadifempty() {
    if (bulletinchamber()) return;  // Si ya hay bala, no hace nada.

    // Vacía todas las cámaras
    for (int i = 0; i < chamber_capacity; i++) {
        chamber[i] = blank; // CAMBIO: era 'empty'
    }

    // Coloca una única bala en una posición aleatoria
    int pos = rand() % chamber_capacity;
    chamber[pos] = bullet;
}

// FUNCIÓN 3: Gira el tambor y dispara
int girarYDisparar() {
    current_position = rand() % chamber_capacity;        // Gira y elige un espacio de la recamara del 1 al 6 
    int bala = chamber[current_position];              // Lee si hay bala
    chamber[current_position] = blank;                 // CAMBIO: era 'empty'
    current_position = (current_position + 1) % chamber_capacity;  // Avanza cámara (opcional)
    return bala;  // 1 = BANG (hubo bala), 0 = CLICK (vacío)
}
//------------------------Programador 2------------------------.

int main() {
    SetConsoleOutputCP(CP_UTF8); // ✅  Activa codificación UTF-8 para mostrar emojis correctamente

    srand(time(0));

    PlaySound("TheSpacexCyberpunk.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

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

        // ✅  Verifica si el usuario ya existe o lo crea
        if (!usuarioExiste(player1.nombre)) {
            textoLento("🆕 New player detected. Creating profile...\n");
            crearUsuario(player1.nombre);
        } else {
            textoLento("👋 Welcome back, " + player1.nombre + "!\n");
        }

        cout << "Enter player 2 name: ";
        cin >> player2.nombre;

        // ✅  Verifica si el usuario ya existe o lo crea
        if (!usuarioExiste(player2.nombre)) {
            textoLento("🆕 New player detected. Creating profile...\n");
            crearUsuario(player2.nombre);
        } else {
            textoLento("👋 Welcome back, " + player2.nombre + "!\n");
        }

    } else {
        cout << "Player name: ";
        cin >> player1.nombre;

        // ✅  Verifica si el usuario ya existe o lo crea
        if (!usuarioExiste(player1.nombre)) {
            textoLento("🆕 New player detected. Creating profile...\n");
            crearUsuario(player1.nombre);
        } else {
            textoLento("👋 Welcome back, " + player1.nombre + "!\n");
        }

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

    registrarVictoria(ganador); // ✅  Registra la victoria del jugador en el historial

    // Detener música cuando el juego termina
    PlaySound(NULL, 0, 0);

    return 0;
}
