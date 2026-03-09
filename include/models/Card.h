/*
CARD_H

Nesta header, definimos a estrutura Card, que representa a carta no jogo
a estrutura Inventory, que representa o inventário de efeitos ativos do player
e a lista Tabuleiro, que representa o tabuleiro do jogo.

createTabuleiro(Tabuleiro &tab) -> Cria o tabuleiro do jogo, embaralhando as cartas.
setCardState(Card &card, State state) -> Altera o estado da carta.
getCardType(Card card) -> Retorna o tipo da carta.

*/
#ifndef CARD_H
#define CARD_H
#include "Enums.h"
#include "../interfaces/DoubleLinkedList.h"
#include "Effect.h"
#include <cstdlib>
#include <ctime>


struct Card
{
    CardName name;
    short identificador;
    State state;
    Type type;
    int parIdentificador;
};


struct Inventory
{
    DoublyLinkedList<ActiveEffect> effects;
};

typedef DoublyLinkedList<Card> Tabuleiro;


Card arr[33] =
{
    {CardName::APPLE, 1, State::OCULTA, Type::NORMAL, 7},
    {CardName::UNIVERSITY, 2, State::OCULTA, Type::NORMAL, 10},
    {CardName::STAR, 3, State::OCULTA, Type::BONUS, 13},
    {CardName::CLOCK, 4, State::OCULTA, Type::NORMAL, 12},
    {CardName::SKULL, 5, State::OCULTA, Type::PENALIDADE, 19},
    {CardName::BOOKS, 6, State::OCULTA, Type::NORMAL, 14},
    {CardName::APPLE, 7, State::OCULTA, Type::NORMAL, 1},
    {CardName::GAMING, 8, State::OCULTA, Type::NORMAL, 15},
    {CardName::DADO, 9, State::OCULTA, Type::NORMAL, 16},
    {CardName::UNIVERSITY, 10, State::OCULTA, Type::NORMAL, 2},
    {CardName::KEY, 11, State::OCULTA, Type::NORMAL, 17},
    {CardName::CLOCK, 12, State::OCULTA, Type::NORMAL, 4},
    {CardName::RAIO, 13, State::OCULTA, Type::BONUS, 3},
    {CardName::BOOKS, 14, State::OCULTA, Type::NORMAL, 6},
    {CardName::GAMING, 15, State::OCULTA, Type::NORMAL, 8},
    {CardName::DADO, 16, State::OCULTA, Type::NORMAL, 9},
    {CardName::KEY, 17, State::OCULTA, Type::NORMAL, 11},
    {CardName::QUEBRA, 18, State::OCULTA, Type::NORMAL, 20},
    {CardName::PROIBIDO, 19, State::OCULTA, Type::PENALIDADE, 5},
    {CardName::QUEBRA, 20, State::OCULTA, Type::NORMAL, 18},
    {CardName::MOON, 21, State::OCULTA, Type::NORMAL, 22},
    {CardName::MOON, 22, State::OCULTA, Type::NORMAL, 21},
    {CardName::MUSIC, 23, State::OCULTA, Type::NORMAL, 24},
    {CardName::MUSIC, 24, State::OCULTA, Type::NORMAL, 23},
    {CardName::HEART, 25, State::OCULTA, Type::NORMAL, 26},
    {CardName::HEART, 26, State::OCULTA, Type::NORMAL, 25},
    {CardName::CROWN, 27, State::OCULTA, Type::NORMAL, 28},
    {CardName::CROWN, 28, State::OCULTA, Type::NORMAL, 27},
    {CardName::FISH, 29, State::OCULTA, Type::NORMAL, 30},
    {CardName::FISH, 30, State::OCULTA, Type::NORMAL, 29},
    {CardName::FOG, 31, State::OCULTA, Type::PENALIDADE, 0},
    {CardName::LOCK, 32, State::OCULTA, Type::PENALIDADE, 0},
    {CardName::HOURGLASS, 33, State::OCULTA, Type::BONUS, 0}
};

void createTabuleiro(Tabuleiro &tab)
{
    /*
    Cria o tabuleiro do jogo, embaralhando as cartas e adicionando-as à lista duplamente encadeada.
    */
    create(tab);

    Card deck[CARDS_COUNT];
    for(int i = 0; i < CARDS_COUNT; i++) deck[i] = arr[i];

    srand((unsigned int)time(NULL));
    for(int i = CARDS_COUNT - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    for(int i = 0; i < CARDS_COUNT; i++)
    {
        Node<Card>* newNode = new Node<Card> {deck[i], NULL, NULL};
        if(tab.start == NULL)
        {
            tab.start = newNode;
            tab.end = newNode;
        }
        else
        {
            tab.end->next = newNode;
            newNode->previous = tab.end;
            tab.end = newNode;
        }
        tab.cardinalidade++;
    }
}

void setCardState(Card &card, State state)
{
    if(state != card.state)  card.state = state;
}

Type getCardType(Card card)
{
    return card.type;
}


#endif
