#pragma once
#include "lib/uint24.h"
#include "stats.hpp"
#include "effect.hpp"
#include "lib/types.hpp"

struct Helment {
    uint8_t id;
    uint8_t armorPoint;
    Effect effect;
    StatModifier modifier;
};

struct Armor {
    uint8_t id;
    uint8_t armorPoint;
    Effect effect;
    StatModifier modifier;
};

struct DamageClass {
    uint8_t rolls;
    uint8_t lowerBound;
    uint8_t upperBound;
};

struct Weapon {
    uint8_t id;
    Effect effect;
    uint8_t armorPoint;
    AttackType type;
    DamageClass damageClass;
    StatModifier modifier;
};

struct EquipmentSlots {
    Helment head;
    Armor armor;
    Weapon weapon;
};
