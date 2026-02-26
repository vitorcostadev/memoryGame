#ifndef Game_H
#define Game_H 
#define CARDS_COUNT 20

#include "../models/Models.h"
#include "Reader.h"
#include "List.h"
#include "DoubleLinkedList.h"

using namespace std;

struct Game{
    Player playerOne, playerTwo;
    unsigned rodadas;
    Tabuleiro cards;
};

void alterarEstado(Card &card){
    card.state = (card.state == State::OCULTA) ? State::VIRADA : State::OCULTA;
}

bool isPar(Card cardOne, Card cardTwo){
    Reader reader;
    create(reader, "../models/cards.csv");
    return getParFromIdent(reader, cardOne.identificador) == getParFromIdent(reader, cardTwo.identificador);
}

void createTabuleiro(Tabuleiro &tab){
    create(tab);
    Cards cards;
    for(int i = 0; i < size(cards._); i++){
        add(tab, get(cards._, i));
    }
}

void createInventory(Inventory &inv){
    if(inv.size > 0) destroy(inv);
    create(inv);
}

void addToInventory(Inventory &inv, int duration, Type type){
    inv.duration = duration;
    add(inv, type);
}

void setPlayers(Game &game, Player player, Player playerTwo){
    game.playerOne = player;
    game.playerTwo = playerTwo;
}


#endif 