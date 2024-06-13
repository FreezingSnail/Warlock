#pragma once
#include <stdint.h>

enum Race {
    HUMAN,
    ELF,
    DWARF,
    ORC,
    GOBLIN,
    TROLL,
    GNOME,
    KOBLOID,
    FAIRY,
    GHOST,
    DEMON,
    ANGEL,
    DRAGON,
    BEAST,
    SKELETON,
    ZOMBIE,
    VAMPIRE,
    WEREWOLF,
    MUMMY,
    WARLOCK,
    LICH,
};

constexpr uint8_t HealthFactor(Race race) {
    uint8_t factor = 0;
    switch (race) {
    case HUMAN:
        factor = 2;
        break;
    case ELF:
        factor = 1;
        break;
    case DWARF:
        factor = 3;
        break;
    case ORC:
        factor = 3;
        break;
    case GOBLIN:
        factor = 1;
        break;
    case TROLL:
        factor = 4;
        break;
    case GNOME:
        factor = 2;
        break;
    case KOBLOID:
        factor = 3;
        break;
    case FAIRY:
        factor = 1;
        break;
    case GHOST:
        factor = 3;
        break;
    case DEMON:
        factor = 4;
        break;
    case ANGEL:
        factor = 4;
        break;
    case DRAGON:
        factor = 5;
        break;
    case BEAST:
        factor = 6;
        break;
    case SKELETON:
        factor = 3;
        break;
    case ZOMBIE:
        factor = 3;
        break;
    case VAMPIRE:
        factor = 2;
        break;
    case WEREWOLF:
        factor = 3;
        break;
    case MUMMY:
        factor = 3;
        break;
    case WARLOCK:
        factor = 5;
        break;
    case LICH:
        factor = 5;
        break;
    }

    return factor;
}