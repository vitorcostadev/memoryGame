#ifndef GAMESERVICE_H
#define GAMESERVICE_H

#include <iostream>
#include <string>
#include "../domain/interfaces/Game.h"
#include "../domain/interfaces/List.h"

using namespace std;

void createPlayers(List<Player, 2> &players, Game &game){
    if(!isEmpty(players)){
        return;
    }

    for(int i = 0; i < 2; i++){
        cout << "Digite o nome do " << (i+1) << " jogador(a): ";
        string name;
        getline(cin, name);

        Player p;
        p.name = name;
        p.points = 0;
        add(players, p);
    }

    setPlayers(game, get(players, 0), get(players, 1));
}

void start(Game &game){
    List<Player, 2> players;
    create(players);
    createPlayers(players, game);
    generateCards(game);

    game.rodadas = CARDS_COUNT / 2;
}

#endif