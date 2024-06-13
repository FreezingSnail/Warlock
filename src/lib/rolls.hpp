#pragma once
#include <stdint.h>
#include "../role.hpp"

uint8_t roll();
uint8_t roll(uint8_t die);
uint8_t roll(Role role);
uint8_t roll(uint8_t count, uint8_t upper, uint8_t lower);
