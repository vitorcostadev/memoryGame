#ifndef Models_H
#define Models_H

#include "../interfaces/DoubleLinkedList.h"
#include "../interfaces/List.h"

using namespace std;

enum CardName{
    APPLE = '🍎',
    UNIVERSITY = '🎓',
    STAR = '⭐',
    CLOCK = '⏰',
    SKULL = '💀',
    BOOKS = '📚',
    GAMING = '🎮',
    DADO = '🎲',
    KEY = '🔑',
    RAIO = '⚡',
    QUEBRA = '💥',
    PROIBIDO = '🚫'
};

enum Type{
    NORMAL,
    BONUS,
    PENALIDADE
};

enum State{
    VIRADA,
    OCULTA
};

struct Card{
    CardName name;
    short identificador;
    State state = State::OCULTA;
    Type type;
    int parIdentificador;
};

struct Player{
    unsigned points;
    List<Card, 2> cards;
    string name;
};

struct Inventory : public DoublyLinkedList<Type>{
    int duration;
};

typedef DoublyLinkedList<Card> Tabuleiro;

List<Card, 20> createCardsList() {
    Card arr[20] = {
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
        {CardName::PROIBIDO, 19, State::OCULTA, Type::PENALIDADE, 1},
        {CardName::QUEBRA, 20, State::OCULTA, Type::NORMAL, 18}
    };
    return of<Card, 20>(arr, 20);
}

struct Cards{
    List<Card, 20> _ = createCardsList();
};

#endif