#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Card.h"

struct Player {
    int points;
    string name;
    Inventory effectInv;
};

#endif