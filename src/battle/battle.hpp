#pragma once
#include "../common.hpp"
#include "../entity.hpp"
#include "action.hpp"

#define MAX_OPPONENTS 3

class Battle {
  public:
    Entity Opponents[MAX_OPPONENTS];
    uint8_t OpponentCount[MAX_OPPONENTS];
    Action actions[PARTY_SIZE];

    void tick();
};