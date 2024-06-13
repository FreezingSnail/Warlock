#include "../../src/lib/rolls.hpp"
#include <cstdlib>

uint8_t roll() {
    return rand() % 20 + 1;
}

uint8_t roll(uint8_t die) {
    return rand() % die + 1;
}

uint8_t roll(Role role) {
    switch (role) {
    case Role::Fighter:
        return rand() % 6 + 1;
    case Role::Tank:
        return rand() % 8 + 1;
    case Role::Theif:
        return rand() % 4 + 1;
    case Role::Wizard:
        return rand() % 4 + 1;
    default:
        return 0;
    }
}

uint8_t roll(uint8_t count, uint8_t upper, uint8_t lower) {
    uint8_t sum = 0;
    for (uint8_t i = 0; i < count; i++) {
        sum += (rand() % (upper - lower + 1)) + lower;
    }
    return sum;
}