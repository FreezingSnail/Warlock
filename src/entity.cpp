#include "entity.hpp"
#include "lib/ReadData.hpp"
#include "lib/rolls.hpp"
#include "race.hpp"

void Entity::LoadEnemy(uint8_t id) {

};

// TODO: put this somewhere more appropriate
static StatModifier LevelUpRolls(uint8_t age) {
    StatModifier statChanges;
    uint8_t chance = roll(4);
    if (chance < 4) {
        uint8_t chance = roll(130);
        if (chance <= age) {
            statChanges.power += 1;
        } else {
            statChanges.power -= 1;
        }
    }
    chance = roll(4);
    if (chance < 4) {
        uint8_t chance = roll(130);
        if (chance <= age) {
            statChanges.finesse += 1;
        } else {
            statChanges.finesse -= 1;
        }
    }
    chance = roll(4);
    if (chance < 4) {
        uint8_t chance = roll(130);
        if (chance <= age) {
            statChanges.mana += 1;
        } else {
            statChanges.mana -= 1;
        }
    }
    chance = roll(4);
    if (chance < 4) {
        uint8_t chance = roll(130);
        if (chance <= age) {
            statChanges.bulk += 1;
        } else {
            statChanges.bulk -= 1;
        }
    }
    chance = roll(4);
    if (chance < 4) {
        uint8_t chance = roll(130);
        if (chance <= age) {
            statChanges.speed += 1;
        } else {
            statChanges.speed -= 1;
        }
    }
    chance = roll(4);
    if (chance < 4) {
        uint8_t chance = roll(130);
        if (chance <= age) {
            statChanges.luck += 1;
        } else {
            statChanges.luck -= 1;
        }
    }

    return statChanges;
}

void Entity::LevelUp(StatModifier statChanges) {
    level++;
    stats.power += statChanges.power;
    stats.finesse += statChanges.finesse;
    stats.mana += statChanges.mana;
    stats.bulk += statChanges.bulk;
    stats.speed += statChanges.speed;
    stats.luck += statChanges.luck;

    uint8_t newHealth = roll(role) + HealthFactor(race) + maxHealth;
    curHealth += newHealth - maxHealth;
    maxHealth = newHealth;
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
    maxHealth = newHealth;
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
/*
    In wizardry:
    Each strike’s chance of hitting is:
    (HitCalcMod + MonsterAC + (3*Victim) - 1) * 5%
*/
uint8_t Entity::AttackRoll(AttackType type) {
    return roll(ClassDie(role)) + GetRollMod(type);
};

uint8_t Entity::DamageRoll(AttackType type) {

    return roll(equipment.weapon.damageClass.rolls, equipment.weapon.damageClass.upperBound, equipment.weapon.damageClass.lowerBound) +
           equipment.weapon.modifier.power + GetRollMod(type);
};