/*
ENUMS_H

Nesta header, estão definidos todos os enums
utilizados no projeto, como os nomes das cartas, os tipos de cartas e os estados das cartas.

CardName -> Enum que armazena os nomes das cartas.
Type -> Enum que armazena os tipos de cartas.
State -> Enum que armazena os estados das cartas.
*/
#ifndef ENUMS_H
#define ENUMS_H

enum CardName : unsigned char
{
    APPLE = 0,
    UNIVERSITY = 1,
    STAR = 2,
    CLOCK = 3,
    SKULL = 4,
    BOOKS = 5,
    GAMING = 6,
    DADO = 7,
    KEY = 8,
    RAIO = 9,
    QUEBRA = 10,
    PROIBIDO = 11,
    MOON = 12,
    MUSIC = 13,
    HEART = 14,
    CROWN = 15,
    FISH = 16,
    FOG = 17,
    LOCK = 18,
    HOURGLASS = 19
};

enum Type
{
    NORMAL,
    BONUS,
    PENALIDADE
};

enum State
{
    VIRADA,
    OCULTA
};


#endif
