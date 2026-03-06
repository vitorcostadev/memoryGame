#ifndef Game_H
#define Game_H 
#define CARDS_COUNT 20

#include <string>
#include "List.h"
#include "DoubleLinkedList.h"
#include "../models/Card.h"
#include "../models/Player.h"

struct Game{
    Player playerOne, playerTwo;
    unsigned rodadas;
    Tabuleiro cards;
};


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
    Node<Card>* current = tab.start;
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

bool isPair(Card c1, Card c2) {
    return (c1.parIdentificador == c2.identificador || 
            c2.parIdentificador == c1.identificador);
}

void start(Game &game) {
    createTabuleiro(game.cards);
}

EffectDef createEffect(Card card){
    EffectDef effect;
    switch (card.name){
        case CardName::PROIBIDO:
            effect.type = EFFECT_SKIP_TURN;
            effect.duration = 1;
            effect.name = "Bloqueio de jogada";
            effect.description = "A próxima rodada do player é ignorada.";
            break;
        default:
            effect.type = EFFECT_EXTRA_TURN;
            effect.duration = 0;
            effect.name = "";
            effect.description = "";
            break;
    }
    return effect;
}

void applyEffect(Player &player, EffectDef eff){
    ActiveEffect active;
    active.definition = eff;
    active.rmDuration = eff.duration;

    add(player.effectInv.effects, active,
        player.effectInv.effects.cardinalidade);
}

bool processEffects(Player &player) {
    bool canPlay = true;
    Node<ActiveEffect>* current = player.effectInv.effects.start;
    int index = 0;
    
    while(current != NULL) {
        if(current->element.definition.type == EFFECT_SKIP_TURN) {
            canPlay = false;
        }

        current->element.rmDuration--;
        
        if(current->element.rmDuration <= 0) {
            cout << player.name << " perdeu o efeito: " 
                 << current->element.definition.name << "\n";
            
            remove(player.effectInv.effects, index);
            current = (index < player.effectInv.effects.cardinalidade) 
                      ? player.effectInv.effects.start 
                      : NULL;
        } else {
            current = current->next;
            index++;
        }
    }
    
    return canPlay;
}

int hasActiveEffect(Player &player, EffectType type) {
    Node<ActiveEffect>* current = player.effectInv.effects.start;
    int index = 0;
    
    while(current != NULL) {
        if(current->element.definition.type == type) {
            return index;  
        }
        current = current->next;
        index++;
    }
    return -1;  
}

#endif 