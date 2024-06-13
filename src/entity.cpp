#include "entity.hpp"
#include "lib/ReadData.hpp"
#include "lib/rolls.hpp"
#include "race.hpp"

void Entity::LoadEnemy(uint8_t id) {

};

uint8_t Entity::GetArmorPoints() {
    return equipment.head.armorPoint + equipment.armor.armorPoint;
};

uint8_t Entity::UpdateHealth(uint8_t damage) {
    curHealth -= damage;
    return curHealth;
};

void Entity::InitialMaxHealth() {
    uint8_t newHealth = 0;
    for (uint8_t i = 0; i < level; i++) {
        newHealth += roll(role) + HealthFactor(race);
    }
};

uint8_t Entity::GetRollMod(AttackType type) {
    uint8_t mod = 0;
    switch (type) {
    case AttackType::Physical:
        mod = stats.power;
        break;
    case AttackType::Ranged:
        mod = stats.finesse;
        break;
    case AttackType::Magic:
        mod = stats.mana;
        break;

    default:
        break;
    }

    return mod;
};

uint8_t Entity::AttackRoll(AttackType type) {
    return roll(ClassDie(role)) + GetRollMod(type);
};

uint8_t Entity::DamageRoll(AttackType type) {

    return roll(equipment.weapon.damageClass.rolls, equipment.weapon.damageClass.upperBound, equipment.weapon.damageClass.lowerBound) +
           equipment.weapon.modifier.power + GetRollMod(type);
};