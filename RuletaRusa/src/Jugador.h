#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>

using namespace std;

struct Player {
    string name;
    int lifes = 3;
    bool poweredBullet = true;
    bool healAvaible = true;
};

#endif