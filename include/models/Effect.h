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