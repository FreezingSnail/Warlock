#pragma once

#define SPRITESU_OVERWRITE
#define SPRITESU_PLUSMASK
#define SPRITESU_RECT
#define SPRITESU_FX
#include "external/SpritesU.hpp"

#include "Animator.hpp"
extern Animator animator;

#define DGF __attribute__((optimize("-O0")))

#define PARTY_SIZE 4

// static void drawStatNumbers(uint8_t x, uint8_t y, uint8_t number) {
//     uint8_t upper = number / 100;
//     uint8_t lower = number % 100;
//     SpritesU::drawPlusMaskFX(x, y, singlenumberswhite, FRAME(upper));
//     SpritesU::drawPlusMaskFX(x + 4, y, numberswhite, FRAME(lower));
// }

// static void drawNumbersBlack(uint8_t x, uint8_t y, uint8_t number) {
//     uint8_t upper = number / 100;
//     uint8_t lower = number % 100;
//     SpritesU::drawPlusMaskFX(x, y, singlenumbersblack, FRAME(upper));
//     SpritesU::drawPlusMaskFX(x + 4, y, numbersblack, FRAME(lower));
// }
