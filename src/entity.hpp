#pragma once
#include "lib/uint24.h"

#include "stats.hpp"
#include "equipment.hpp"
#include "race.hpp"
#include "role.hpp"
#include "lib/types.hpp"

class Entity {
  public:
    uint8_t level;
    uint8_t curHealth;
    uint8_t maxHealth;
    Stats stats;
    Race race;
    Role role;
    EquipmentSlots equipment;

    void LoadEnemy(uint8_t id);

    void InitialMaxHealth();
    void LevelUp(StatModifier statChanges);

    uint8_t UpdateHealth(uint8_t damage);
    uint8_t GetArmorPoints();
    uint8_t GetRollMod(AttackType type);
    uint8_t AttackRoll(AttackType type);
    uint8_t DamageRoll(AttackType type);
};
