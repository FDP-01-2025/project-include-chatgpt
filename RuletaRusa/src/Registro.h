#ifndef RECORD_H
#define RECORD_H

#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

// Verifica si el usuario ya existe
bool userExists(const string& searchedName) {
    ifstream input("registro_victorias.txt");
    string name, label;
    int wins;

    while (input >> name >> label >> wins) {
        if (name == searchedName) {
            return true;
        }
    }

    return false;
}

// Crea un nuevo usuario con 0 victorias
void createUser(const string& newName) {
    ofstream output("registro_victorias.txt", ios::app);
    output << newName << " wins: 0" << endl;
}

// Suma +1 victoria al jugador, o lo crea si no existía
void registerWin(const string& winnerName) {
    ifstream input("registro_victorias.txt");
    ofstream tempOutput("temp.txt");

    string name, label;
    int wins;
    bool found = false;

    while (input >> name >> label >> wins) {
        if (name == winnerName) {
            wins++;
            found = true;
        }
        tempOutput << name << " wins: " << wins << endl;
    }

    input.close();

    if (!found) {
        tempOutput << winnerName << " wins: 1" << endl;
    }

    tempOutput.close();
    remove("registro_victorias.txt");
    rename("temp.txt", "registro_victorias.txt");
}

#endif
