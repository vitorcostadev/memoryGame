#ifndef Models_H
#define Models_H

#include "../interfaces/DoubleLinkedList.h"
#include "../interfaces/List.h"

using namespace std;

enum CardName{
    APPLE,
    UNIVERSITY,
    STAR,
    CLOCK,
    SKULL,
    BOOKS,
    GAMING,
    DADO,
    KEY,
    RAIO,
    QUEBRA,
    PROIBIDO
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
};

inline ostream& operator<<(ostream& os, const Card& card) {
    os << "Card{id=" << card.identificador
       << ", state=" << (card.state == State::OCULTA ? "OCULTA" : "REVELADA")
       << "}";
    return os;
}

struct Player{
    unsigned points;
    List<Card, 2> cards;
    string name;
};

struct Inventory : public DoublyLinkedList<Type>{
    int duration;
};

typedef DoublyLinkedList<Card> Tabuleiro;

inline List<Card, 20> createCardsList() {
    Card arr[20] = {
        {CardName::APPLE, 1, State::OCULTA, Type::NORMAL},
        {CardName::UNIVERSITY, 2, State::OCULTA, Type::NORMAL},
        {CardName::STAR, 3, State::OCULTA, Type::BONUS},
        {CardName::CLOCK, 4, State::OCULTA, Type::NORMAL},
        {CardName::SKULL, 5, State::OCULTA, Type::PENALIDADE},
        {CardName::BOOKS, 6, State::OCULTA, Type::NORMAL},
        {CardName::APPLE, 7, State::OCULTA, Type::NORMAL},
        {CardName::GAMING, 8, State::OCULTA, Type::NORMAL},
        {CardName::DADO, 9, State::OCULTA, Type::NORMAL},
        {CardName::UNIVERSITY, 10, State::OCULTA, Type::NORMAL},
        {CardName::KEY, 11, State::OCULTA, Type::NORMAL},
        {CardName::CLOCK, 12, State::OCULTA, Type::NORMAL},
        {CardName::RAIO, 13, State::OCULTA, Type::BONUS},
        {CardName::BOOKS, 14, State::OCULTA, Type::NORMAL},
        {CardName::GAMING, 15, State::OCULTA, Type::NORMAL},
        {CardName::DADO, 16, State::OCULTA, Type::NORMAL},
        {CardName::KEY, 17, State::OCULTA, Type::NORMAL},
        {CardName::QUEBRA, 18, State::OCULTA, Type::NORMAL},
        {CardName::PROIBIDO, 19, State::OCULTA, Type::PENALIDADE},
        {CardName::QUEBRA, 20, State::OCULTA, Type::NORMAL}
    };
    return of<Card, 20>(arr, 20);
}

struct Cards{
    List<Card, 20> _ = createCardsList();
};

#endif