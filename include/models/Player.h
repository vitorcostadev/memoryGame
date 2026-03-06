#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../interfaces/List.h"
#include "Card.h"

struct Player {
    int points;
    List<Card, 2> cards;
    string name;
    Inventory effectInv;
};

#endif