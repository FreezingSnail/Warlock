#pragma once
#include "lib/uint24.h"

struct Stats {
    uint8_t power;     // physical
    uint8_t finesse;   // ranged
    uint8_t bulk;      // health
    uint8_t mana;      // magic
    uint8_t speed;     // initiative
    uint8_t luck;      // rng
};

struct StatModifier {
    uint8_t power : 4;     // physical
    uint8_t finesse : 4;   // ranged
    uint8_t bulk : 4;      // health
    uint8_t mana : 4;      // magic
    uint8_t speed : 4;     // initiative
    uint8_t luck : 4;      // rng
};