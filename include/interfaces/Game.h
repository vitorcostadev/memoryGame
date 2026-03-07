#ifndef Game_H
#define Game_H 
#define CARDS_COUNT 20
#define MAX_ROUNDS 30

#include <iostream>
#include <string>
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
    game.rodadas = 0;
    game.playerOne.points = 0;
    game.playerTwo.points = 0;
    create(game.playerOne.effectInv.effects);
    create(game.playerTwo.effectInv.effects);
    createTabuleiro(game.cards);
}

EffectDef createEffect(Card card){
    EffectDef effect;
    switch (card.name){
        case CardName::PROIBIDO:
            effect.type = EFFECT_SKIP_TURN;
            effect.duration = 1;
            effect.name = "Bloqueio de jogada";
            effect.description = "A proxima rodada do jogador é ignorada.";
            break;
        case CardName::SKULL:
            effect.type = EFFECT_SKIP_TURN;
            effect.duration = 1;
            effect.name = "Paralisia";
            effect.description = "A proxima rodada do jogador é bloqueada.";
            break;
        case CardName::STAR:
            effect.type = EFFECT_EXTRA_TURN;
            effect.duration = 1;
            effect.name = "Jogada extra";
            effect.description = "Jogador ganha mais uma jogada.";
            break;
        case CardName::RAIO:
            effect.type = EFFECT_REMOVE_PENALTY;
            effect.duration = 0;
            effect.name = "Remocao de penalidade";
            effect.description = "Remove uma penalidade ativa do inventario.";
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

void removeFirstPenalty(Player &player) {
    Node<ActiveEffect>* current = player.effectInv.effects.start;
    int index = 0;
    while(current != NULL) {
        if(current->element.definition.type == EFFECT_SKIP_TURN) {
            cout << player.name << ": penalidade removida por bônus: "
                 << current->element.definition.name << "\n";
            remove(player.effectInv.effects, index);
            return;
        }
        current = current->next;
        index++;
    }
    cout << player.name << ": nenhuma penalidade ativa para remover.\n";
}

void applyEffect(Player &player, EffectDef eff){
    if(eff.type == EFFECT_REMOVE_PENALTY) {
        removeFirstPenalty(player);
        return;
    }
    if(eff.name.empty()) return;
    ActiveEffect active;
    active.definition = eff;
    active.rmDuration = eff.duration;

    add(player.effectInv.effects, active,
        player.effectInv.effects.cardinalidade);
}

bool processEffects(Player &player) {
    bool canPlay = true;
    int i = 0;
    Node<ActiveEffect>* node = player.effectInv.effects.start;

    while(node != NULL) {
        Node<ActiveEffect>* next = node->next;

        if(node->element.definition.type == EFFECT_SKIP_TURN)
            canPlay = false;

        node->element.rmDuration--;

        if(node->element.rmDuration <= 0) {
            cout << player.name << ": efeito expirou: "
                 << node->element.definition.name << "\n";
            remove(player.effectInv.effects, i);
        } else {
            i++;
        }

        node = next;
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