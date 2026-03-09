/*
PLAYER_H

addPoints(Player &player, int points) -> Adiciona pontos ao player.
getPlayerPoints(Player player) -> Retorna o nome do player.
setPlayerName(Player &player, string name) -> Atualiza o nome do player.

struct Player -> Armazena os pontos, nomes e o inventário de efeitos.
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Card.h"

struct Player
{
    int points;
    string name;
    Inventory effectInv;
};

void addPoints(Player &player, int points)
{
    if(points < 0) return;

    player.points += points;
}

int getPlayerPoints(Player player)
{
    return player.points;
}

string getPlayerName(Player player)
{
    return player.name;
}

void setPlayerName(Player &player, string name)
{
    if(name.empty()) return;
    player.name = name;
}
#endif
