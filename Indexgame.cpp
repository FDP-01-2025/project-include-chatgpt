#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

void registrarVictoria(string nombreGanador) {
    ifstream entrada("registro_victorias.txt");
    ofstream salidaTemp("temp.txt");
    string nombre;
    int victorias;
    bool encontrado = false; }

    

struct Jugador {
    string nombre;
    int vidas = 3;
    bool corteDisponible = true;
    bool curacionDisponible = true;
};

void imprimirEstado(Jugador j1, Jugador j2) {
    cout << "\n=======================\n";
    cout << j1.nombre << " | Vidas: " << j1.vidas << " ❤️\n";
    cout << j2.nombre << " | Vidas: " << j2.vidas << " ❤️\n";
    cout << "=======================\n";
}

int girarTambor() {
    return rand() % 6;  // Número entre 0 y 5
}

bool disparar() {
    return rand() % 6 == 0;  // 1 en 6 posibilidades de que dispare
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

int main() {
    srand(time(0));
    Jugador jugador1, jugador2;
    int modo;

    cout << "🎲 Bienvenido a la Ruleta Rusa 🎲\n";
    cout << "1. 2 Jugadores\n";
    cout << "2. 1 Jugador vs CPU\n";
    cout << "Selecciona modo de juego: ";
    cin >> modo;

    if (modo == 1) {
        cout << "Nombre del Jugador 1: ";
        cin >> jugador1.nombre;
        cout << "Nombre del Jugador 2: ";
        cin >> jugador2.nombre;
    } else {
        cout << "Nombre del Jugador: ";
        cin >> jugador1.nombre;
        jugador2.nombre = "💻 CPU";
    }

    // Bucle del juego
    while (estaVivo(jugador1) && estaVivo(jugador2)) {
        imprimirEstado(jugador1, jugador2);
        turnoJugador(jugador1, jugador2);
        if (!estaVivo(jugador1)) break;

        imprimirEstado(jugador1, jugador2);
        if (jugador2.nombre == "💻 CPU") {
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

    cout << "\n🎉 ¡FIN DEL JUEGO! 🎉\n";
    if (estaVivo(jugador1)) cout << jugador1.nombre << " gana!\n";
    else cout << jugador2.nombre << " gana!\n";



    

    return 0;
}



   
