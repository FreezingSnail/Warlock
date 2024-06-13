#include <ArduboyFX.h>
#include "src/fxdata.h"

#include "src/GameState.hpp"
GameState gameState;

Arduboy2 arduboy;

void setup() {
    arduboy.begin();
    arduboy.initRandomSeed();

    FX::begin(FX_DATA_PAGE);
    // FX::setFont(ArduFont, dcmNormal);   // select default font
    FX::setCursorRange(0, 32767);
    gameState = GameState();
}

void run() {
}

void render() {
    arduboy.clear();
    arduboy.display();
}

void loop() {
    if (!arduboy.nextFrame())
        return;

    run();
    render();
}
