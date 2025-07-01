#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

// ✅ FUNCIÓN para registrar victoria en archivo
void registrarVictoria(string nombreGanador)
{
    ifstream entrada("registro_victorias.txt");
    ofstream salidaTemp("temp.txt");
    string nombre;
    string etiqueta;
    int victorias;
    bool encontrado = false;

    while (entrada >> nombre >> etiqueta >> victorias)
    {
        if (nombre == nombreGanador)
        {
            victorias++;
            encontrado = true;
        }
        salidaTemp << nombre << " victorias: " << victorias << endl;
    }

    entrada.close();

    if (!encontrado)
    {
        salidaTemp << nombreGanador << " victorias: 1" << endl;
    }

    salidaTemp.close();

    remove("registro_victorias.txt");
    rename("temp.txt", "registro_victorias.txt");
}

// ============================
struct Jugador
{
    string nombre;
    int vidas = 3;
    bool corteDisponible = true;
    bool curacionDisponible = true;
};

void imprimirEstado(Jugador j1, Jugador j2)
{
    cout << "\n=======================\n";
    cout << j1.nombre << " | Vidas: " << j1.vidas << " ❤️\n";
    cout << j2.nombre << " | Vidas: " << j2.vidas << " ❤️\n";
    cout << "=======================\n";
}

int girarTambor()
{
    return rand() % 6;
}

bool disparar()
{
    return rand() % 6 == 0;
}

void turnoJugador(Jugador &jugador, Jugador &oponente)
{
    cout << "\nEs el turno de " << jugador.nombre << "...\n";
    cout << "1. Girar recámara\n";
    cout << "2. Dispararte\n";
    if (jugador.corteDisponible)
        cout << "3. Usar CORTE (doble daño)\n";
    if (jugador.curacionDisponible)
        cout << "4. Usar CURACIÓN (+1 vida)\n";
    cout << "Elige una opción: ";

    int opcion;
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        cout << "🔄 Giraste la recámara...\n";
        break;
    case 2:
        cout << "🔫 Te apuntaste y jalaste el gatillo...\n";
        if (disparar())
        {
            cout << "💥 BANG! Perdiste una vida.\n";
            jugador.vidas -= 1;
        }
        else
        {
            cout << "🫣 CLICK! No salió la bala.\n";
        }
        break;
    case 3:
        if (jugador.corteDisponible)
        {
            cout << "⚔️ Usaste CORTE. El daño será doble si te toca la bala.\n";
            if (disparar())
            {
                cout << "💥 BANG! Perdiste 2 vidas.\n";
                jugador.vidas -= 2;
            }
            else
            {
                cout << "🫣 CLICK! Te salvaste.\n";
            }
            jugador.corteDisponible = false;
        }
        else
        {
            cout << "❌ No tienes CORTE disponible.\n";
        }
        break;
    case 4:
        if (jugador.curacionDisponible)
        {
            cout << "💊 Usaste CURACIÓN. Recuperaste 1 vida.\n";
            jugador.vidas += 1;
            jugador.curacionDisponible = false;
        }
        else
        {
            cout << "❌ Ya usaste tu curación.\n";
        }
        break;
    default:
        cout << "Opción inválida.\n";
    }
}

bool estaVivo(Jugador j)
{
    return j.vidas > 0;
}

// -------------------- Programa 3 Luis --------------------

// Guarda el resultado de una partida
void guardarResultado(string nombreJugador1, string nombreJugador2, string ganador, int rondasTotales)
{
    ofstream archivo("resultados_partida.txt", ios::app);
    if (archivo.is_open())
    {
        archivo << "Jugador 1: " << nombreJugador1 << endl;
        archivo << "Jugador 2: " << nombreJugador2 << endl;
        archivo << "Ganador: " << ganador << endl;
        archivo << "Rondas jugadas: " << rondasTotales << endl;
        archivo << "-----------------------------" << endl;
        archivo.close();
        cout << "\n✅ Resultado guardado en 'resultados_partida.txt'.\n";
    }
    else
    {
        cerr << "❌ Error al guardar el archivo.\n";
    }
}

// Muestra las partidas anteriores
void leerPartidasAnteriores()
{
    ifstream archivo("resultados_partida.txt");
    string linea;
    cout << "\n📜 Partidas anteriores:\n";
    cout << "-----------------------------\n";
    if (archivo.is_open())
    {
        while (getline(archivo, linea))
        {
            cout << linea << endl;
        }
        archivo.close();
    }
    else
    {
        cout << "⚠️ No hay partidas guardadas o no se puede leer el archivo.\n";
    }
}

// Muestra estadísticas al finalizar la partida
void mostrarEstadisticasFinales(string ganador, int rondas)
{
    cout << "\n📊 Estadísticas Finales:\n";
    cout << "Ganador: " << ganador << endl;
    cout << "Rondas jugadas: " << rondas << endl;
}

int main()
{
    srand(time(0));
    Jugador jugador1, jugador2;
    int rondas = 0;
    int modo;
    string ganadores[10]; // Array para guardar temporalmente los ganadores
    int totalGanadores = 0;

    leerPartidasAnteriores(); // Mostrar historial antes de jugar

    cout << "🎲 Bienvenido a la Ruleta Rusa 🎲\n";
    cout << "1. 2 Jugadores\n";
    cout << "2. 1 Jugador vs CPU\n";
    cout << "Selecciona modo de juego: ";
    cin >> modo;

    if (modo == 1)
    {
        cout << "Nombre del Jugador 1: ";
        cin >> jugador1.nombre;
        cout << "Nombre del Jugador 2: ";
        cin >> jugador2.nombre;
    }
    else
    {
        cout << "Nombre del Jugador: ";
        cin >> jugador1.nombre;
        jugador2.nombre = "CPU";
    }

    while (estaVivo(jugador1) && estaVivo(jugador2))
    {
        imprimirEstado(jugador1, jugador2);
        turnoJugador(jugador1, jugador2);
        if (!estaVivo(jugador1))
            break;

        imprimirEstado(jugador1, jugador2);
        if (jugador2.nombre == "CPU")
        {
            cout << "\nTurno de la CPU...\n";
            if (disparar())
            {
                cout << "💻 CPU se disparó... ¡y se dio!\n";
                jugador2.vidas -= 1;
            }
            else
            {
                cout << "💻 CPU jaló el gatillo... nada pasó.\n";
            }
        }
        else
        {
            turnoJugador(jugador2, jugador1);
        }
    }

    cout << "\n🎉 ¡FIN DEL JUEGO! 🎉\n";
    string ganador;
    if (estaVivo(jugador1))
    {
        cout << jugador1.nombre << " gana!\n";
        ganador = jugador1.nombre;
    }
    // Guardar el nombre del ganador en el array
    else if (totalGanadores < 10)
    {
        ganadores[totalGanadores] = ganador;
        totalGanadores++;
    }

    else
    {
        cout << jugador2.nombre << " gana!\n";
        ganador = jugador2.nombre;
    }

    // ✅ Aquí se registra la victoria
    registrarVictoria(ganador);
    // Mostrar los ganadores guardados en la sesión
    cout << "\n🏆 Ganadores en esta sesión:\n";
    for (int i = 0; i < totalGanadores; i++)
    {
        cout << i + 1 << ". " << ganadores[i] << endl;
    }

    // Mostrar estadísticas y guardar en archivo
    mostrarEstadisticasFinales(ganador, rondas);
    guardarResultado(jugador1.nombre, jugador2.nombre, ganador, rondas);

    return 0;
}
