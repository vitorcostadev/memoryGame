#ifndef Game_H
#define Game_H 
#define CARDS_COUNT 20

#include "../models/Models.h"
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

void generateCards(Game &game){
    createTabuleiro(game.cards);
}

string getEmoji(CardName name){
    switch(name){
        case APPLE: return "\xF0\x9F\x8D\x8E";      
        case UNIVERSITY: return "\xF0\x9F\x8F\xAB"; 
        case STAR: return "\xE2\xAD\x90";           
        case CLOCK: return "\xE2\x8F\xB0";          
        case SKULL: return "\xF0\x9F\x92\x80";     
        case BOOKS: return "\xF0\x9F\x93\x9A";      
        case GAMING: return "\xF0\x9F\x8E\xAE";     
        case DADO: return "\xF0\x9F\x8E\xB2";       
        case KEY: return "\xF0\x9F\x94\x91";        
        case RAIO: return "\xE2\x9A\xA1";           
        case QUEBRA: return "\xF0\x9F\x92\xA5";     
        case PROIBIDO: return "\xF0\x9F\x9A\xAB";   
        default: return "?";
    }
}

string generateMapEmoji(Game game) {
    /*
    
    */
    string emojiMap;

    Nodo<Card>* current = game.cards.start;
    while(current != NULL){
        emojiMap += getEmoji(current->element.name) + " ";
        current = current->next;
    }
    return emojiMap;
}

#endif 