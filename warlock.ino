#include <ArduboyFX.h>
#include <stdint.h>
#include "src/fxdata.h"
#include <ArduboyRaycast_RenderFX.h>

#include "src/external/raycast/bg_full.h"

#include "src/GameState.hpp"
GameState gameState;

Arduboy2 arduboy;

constexpr uint8_t FRAMERATE = 20;   // 35 is a safe number for fullscreen raycasting (no sprites)
constexpr float MOVESPEED = 0.7f / FRAMERATE;
constexpr float ROTSPEED = 1.45f / FRAMERATE;

uint8_t x, y;

uint8_t level[8 * 8];

RcMap worldMap{level, 8, 8};

RcPlayer player;
RcRender<64, HEIGHT> renderer;

uflot intensity = 1.0;
bool isSolid(uflot x, uflot y) {
    // If youve seen the `basic_tilesonly` example, you might notice that the RcContainer
    // simply contains all those other special classes and barely has any functionality on its
    // own. As a result, this collision detection doesn't have to change

    uint8_t tile = worldMap.getCell(x.getInteger(), y.getInteger());

    // return (tile != 0 && tile != MyTiles::OutdoorRockOpening) ||
    return false;   // (tile != 0);
}

void readMap() {
    FX::seekData(test_dungeon_raycast + 2);
    // FX::readBytes(mapBuffer, 8 * 8);
    FX::readBytes(level, 8 * 8);
    FX::readEnd();
}

// You have to write this yourself but I provide a helper function which automatically does
// bounds checking on the map and other defined bounding boxes, as long as you provide a
// function which says whether something is a collision (see above)
void movement() {
    float movement = 0;
    float rotation = 0;

    // Simple movement forward and backward
    if (arduboy.pressed(UP_BUTTON))
        movement = MOVESPEED;
    if (arduboy.pressed(DOWN_BUTTON))
        movement = -MOVESPEED;

    // Simple rotation
    if (arduboy.pressed(RIGHT_BUTTON))
        rotation = -ROTSPEED;
    if (arduboy.pressed(LEFT_BUTTON))
        rotation = ROTSPEED;

    // Same here: instead of getting player out of the container like in the previous example,
    // we can simply go straight to the player to try movement
    player.tryMovement(movement, rotation, &isSolid);
}

void flashlight() {

    // about ~0.25 gives you 2 block distance, .5 3 blocks
    // 0.07 bare min to navigate or so

    if (arduboy.justPressed(A_BUTTON)) {
        intensity += 0.01;
        // render.setLightIntensity(intensity);
    }
    if (arduboy.justPressed(B_BUTTON)) {
        intensity -= 0.01;
        // render.setLightIntensity(intensity);
    }
}

void setup() {
    arduboy.begin();
    arduboy.initRandomSeed();
    arduboy.setFrameRate(FRAMERATE);

    FX_INIT();
    // FX::setFont(ArduFont, dcmNormal);   // select default font
    FX::setCursorRange(0, 32767);
    x = 1;

    gameState = GameState();

    readMap();
    player.posX = 4.5;
    player.posY = 3.5;
    player.dirX = 1;
    player.dirY = 1;

    worldMap.map = level;
    renderer.tilesheet = tilesheet;
    renderer.setLightIntensity(intensity);
    renderer.shading = RcShadingType::Black;
    player.initPlayerDirection(0, 0.75);
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
    arduboy.pollButtons();
    // renderer.clearRaycast(&arduboy);
    FX::display(CLEAR_BUFFER);
    // Process player interaction, or however you'd like to do it
    movement();
    flashlight();

    x = player.posX.getInteger();
    y = player.posY.getInteger();

    if (arduboy.frameCount % 5 == 0) {
        renderer.setLightIntensity(0.5 + sin(arduboy.frameCount) * 0.25);
    }
    // It's too expensive to draw a true raycast floor, so you're stuck with just drawing a background
    // that's "good enough". The background is large enough to clear the screen, hence why we didn't call
    // "clearRaycast" above
    // Sprites::drawOverwrite(0, 0, bg_full, 0);

    // Instead of calling 'runIteration' on the container, we simply directly call the
    // renderer to render the raycast walls. We don't have to do the sprite stuff
    // renderer.raycastWalls(&player, &worldMap, &arduboy);
    // FX::drawBitmap(30, 64 - 16, torch, (arduboy.frameCount / 5) % torchFrames, dbmMasked);

    renderer.raycastWalls(&player, &worldMap, &arduboy);

    arduboy.setCursor(0, 0);
    arduboy.print(" ");
    arduboy.print(x);
    arduboy.print(",");
    arduboy.print(y);
    arduboy.print(",");
    arduboy.print(worldMap.getCell(x, y));

    FX::drawBitmap(30, 64 - 16, torch, (arduboy.frameCount / 5) % 2, dbmMasked);

    // arduboy.display();
}
