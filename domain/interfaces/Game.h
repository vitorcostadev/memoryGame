#ifndef Game_H
#define Game_H 
#define CARDS_COUNT 20

#include "../models/Models.h"
#include "List.h"
#include "DoubleLinkedList.h"
#include <string>

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
    
    List<Card, 20> cardList = createCardsList();
    for(int i = 0; i < size(cardList); i++){
        add(tab, get(cardList, i));
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

void isPair(Card &card1, Card &card2){
    if(card1.parIdentificador == card2.parIdentificador){
        alterarEstado(card1);
        alterarEstado(card2);
    }
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

string generateMapEmoji(const Tabuleiro &tab, int cols = 5){
    string emojiMap;
    Nodo<Card>* current = tab.start;
    int idx = 0;
    while(current != NULL){
        if(current->element.state == State::OCULTA){
            emojiMap += "?";
        } else {
            emojiMap += getEmoji(current->element.name);
        }
        idx++;
        if(idx % cols == 0) emojiMap += "\n";
        else emojiMap += " ";
        current = current->next;
    }
    return emojiMap;
}

#endif 