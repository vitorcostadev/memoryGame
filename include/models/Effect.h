/*
EFFECT_H

EffectType -> Enumeração dos tipos de efeitos.
EffectDef - struct que armazena a definição de um efeito, sua duração, nome e descrição.
ActiveEffect - struct que armazena um efeito ativo, sua definição e a duração restante.

As subrotinas estão implementados em Game.h
*/
#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include "../interfaces/DoubleLinkedList.h"

using namespace std;

enum EffectType{
    EFFECT_EXTRA_TURN,
    EFFECT_SKIP_TURN,
    EFFECT_REMOVE_PENALTY
};

struct EffectDef{
    EffectType type;
    int duration;
    string name, description;
};

struct ActiveEffect{
    EffectDef definition;
    int rmDuration;
};

#endif