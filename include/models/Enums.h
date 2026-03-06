#ifndef ENUMS_H
#define ENUMS_H

enum CardName : unsigned char {
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
    PROIBIDO = 11
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


#endif 