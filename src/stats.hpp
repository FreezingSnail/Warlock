#pragma once
#include "lib/uint24.h"

struct Stats {
    uint8_t power;     // physical
    uint8_t finesse;   // ranged
    uint8_t bulk;      // health
    uint8_t mana;      // magic
    uint8_t luck;      // rng
};