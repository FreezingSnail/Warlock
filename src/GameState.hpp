#pragma once

#include "lib/uint24.h"
#include "entity.hpp"

class GameState {
  public:
    Entity party[4];
    Entity Opponents[3];

    GameState();
};