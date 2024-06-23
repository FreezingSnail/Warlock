#include <ArduboyFX.h>
#include <stdint.h>
#include "src/fxdata.h"
#include <ArduboyRaycast_RenderFX.h>

#include "src/external/raycast/bg_full.h"

#include "src/GameState.hpp"
#include "src/world/mapBuffer.hpp"

MapBuffer mapBuffer;
GameState gameState;

Arduboy2 arduboy;

enum DIR { NORTH, EAST, SOUTH, WEST };
DIR dir = NORTH;

constexpr uint8_t FRAMERATE = 20;   // 35 is a safe number for fullscreen raycasting (no sprites)
constexpr float MOVESPEED = 0.7f / FRAMERATE;
constexpr float ROTSPEED = 1.45f / FRAMERATE;

uint8_t testMap[64] = {1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1};

uflot x, y;

uint8_t state = 0;

RcMap worldMap{mapBuffer.buffer, BUFFER_HEIGHT, BUFFER_WIDTH};

RcPlayer player;
RcRender<128, HEIGHT> renderer;

uflot intensity = 1.0;
bool isSolid(uflot x, uflot y) {
    // If youve seen the `basic_tilesonly` example, you might notice that the RcContainer
    // simply contains all those other special classes and barely has any functionality on its
    // own. As a result, this collision detection doesn't have to change

    uint8_t tile = worldMap.getCell(x.getInteger(), y.getInteger());

    // return (tile != 0 && tile != MyTiles::OutdoorRockOpening) ||
    return (tile != 0);
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
        state++;
        // render.setLightIntensity(intensity);
    }
    if (arduboy.justPressed(B_BUTTON)) {
        intensity -= 0.01;
        state--;
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

    gameState = GameState();
    mapBuffer.initMap(test_dungeon_raycast);

    player.posX = CENTER_X + 0.5;
    player.posY = CENTER_Y + 0.5;

    player.dirX = 1;
    player.dirY = 1;

    // worldMap.map = mapBuffer.buffer;
    renderer.tilesheet = tilesheet;
    renderer.setLightIntensity(intensity);
    renderer.shading = RcShadingType::Black;
    // renderer.altWallShading = RcShadingType::None;
    // player.initPlayerDirection(0, 0.75);

    x = player.posX;
    y = player.posY;
    Serial.print(mapBuffer.originX);
    Serial.print(",");
    Serial.println(mapBuffer.originY);
}

void run() {
}

void render() {
    arduboy.clear();
    arduboy.display();
}

void direction() {
    if ((player.dirX >= -1 && player.dirX <= 1) && (player.dirY >= 1 && player.dirY <= 1.5)) {
        dir = SOUTH;
    } else if ((player.dirX >= .5 && player.dirX <= 1.5) && (player.dirY >= -1 && player.dirY <= 1)) {
        dir = WEST;
    } else if ((player.dirX >= -1 && player.dirX <= 1) && (player.dirY >= -1.5 && player.dirY <= -1)) {
        dir = NORTH;
    } else {
        dir = EAST;
    }
}

static uint16_t map2Dto1D(uint16_t x, uint16_t y, uint8_t width) {
    return (y * width) + x;
}
void draw() {
    Arduboy2::drawRect(17, 17, BUFFER_WIDTH * 4 + 4, BUFFER_HEIGHT * 4 + 4, WHITE);
    Arduboy2::fillRect(18, 18, BUFFER_WIDTH * 4 + 2, BUFFER_HEIGHT * 4 + 2, BLACK);
    for (uint8_t y = 0; y < BUFFER_HEIGHT; y++) {
        for (uint8_t x = 0; x < BUFFER_WIDTH; x++) {
            uint8_t tile = mapBuffer.buffer[map2Dto1D(x, y, BUFFER_WIDTH)];

            if (tile == 0) {
                Arduboy2Base::fillRect(20 + ((BUFFER_WIDTH - x - 1) * 4), 20 + (y * 4), 3, 3, WHITE);
            }

            if (x == CENTER_X && y == CENTER_Y) {
                Arduboy2Base::drawPixel(20 + ((BUFFER_WIDTH - x - 1) * 4) + 1, 20 + (y * 4) + 1, BLACK);
            }
        }
    }
    switch (dir) {
    case NORTH:
        Arduboy2Base::drawPixel(20 + ((BUFFER_WIDTH - 4 - 1) * 4) + 1, 20 + (4 * 4), BLACK);

        break;

    case EAST:
        Arduboy2Base::drawPixel(20 + ((BUFFER_WIDTH - 4 - 1) * 4) + 2, 20 + (4 * 4) + 1, BLACK);

        break;

    case SOUTH:
        Arduboy2Base::drawPixel(20 + ((BUFFER_WIDTH - 4 - 1) * 4) + 1, 20 + (4 * 4) + 2, BLACK);
        break;

    case WEST:
        Arduboy2Base::drawPixel(20 + ((BUFFER_WIDTH - 4 - 1) * 4), 20 + (4 * 4) + 1, BLACK);
        break;
    }
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
    direction();

    if ((x.getInteger() != player.posX.getInteger() || y.getInteger() != player.posY.getInteger())) {
        int xDelta, yDelta;
        if (x.getInteger() < player.posX.getInteger()) {
            xDelta = 1;
        } else if (x.getInteger() > player.posX.getInteger()) {
            xDelta = -1;
        } else {
            xDelta = 0;
        }
        if (y.getInteger() < player.posY.getInteger()) {
            yDelta = 1;
        } else if (y.getInteger() > player.posY.getInteger()) {
            yDelta = -1;
        } else {
            yDelta = 0;
        }
        Serial.print("loading map: ");
        Serial.print(mapBuffer.originX);
        Serial.print(",");
        Serial.print(mapBuffer.originY);
        Serial.print(" : ");
        Serial.print(mapBuffer.originX + xDelta);
        Serial.print(",");
        Serial.print(mapBuffer.originY + yDelta);
        Serial.print("\n");

        mapBuffer.loadMap(mapBuffer.originX + xDelta, mapBuffer.originY + yDelta);

        Serial.print("pos: ");
        Serial.print(player.posX.getFraction());
        Serial.print(",");
        Serial.print(player.posX.getFraction());
        // player.posX = uflot(3) + player.posX.getFraction();
        // player.posY = uflot(3) + player.posY.getFraction();
        player.posX = CENTER_X + (player.posX - player.posX.getInteger());
        player.posY = CENTER_Y + (player.posY - player.posY.getInteger());

        x = player.posX;
        y = player.posY;

        Serial.print(" : after  ");
        Serial.print(player.posX.getFraction());
        Serial.print(",");
        Serial.print(player.posX.getFraction());
        Serial.print("\n");
    }

    if (arduboy.frameCount % 5 == 0) {
        renderer.setLightIntensity(0.5 + sin(arduboy.frameCount) * 0.1);
    }
    // It's too expensive to draw a true raycast floor, so you're stuck with just drawing a background
    // that's "good enough". The background is large enough to clear the screen, hence why we didn't call
    // "clearRaycast" above
    // Sprites::drawOverwrite(0, 0, bg_full, 0);

    // Instead of calling 'runIteration' on the container, we simply directly call the
    // renderer to render the raycast walls. We don't have to do the sprite stuff
    // renderer.raycastWalls(&player, &worldMap, &arduboy);
    // FX::drawBitmap(30, 64 - 16, torch, (arduboy.frameCount / 5) % torchFrames, dbmMasked);

    if (state == 0) {
        renderer.raycastWalls(&player, &worldMap, &arduboy);
        arduboy.setCursor(0, 0);
        arduboy.print(" ");
        arduboy.print(player.posX.getInteger());
        arduboy.print(",");
        arduboy.print(player.posY.getInteger());
        arduboy.print(",");
        arduboy.print(worldMap.getCell(x.getInteger(), y.getInteger()));
        FX::drawBitmap(30, 64 - 16, torch, (arduboy.frameCount / 5) % 2, dbmMasked);

    } else {
        draw();
        Arduboy2::setCursor(80, 10);
        switch (dir) {
        case NORTH:
            arduboy.print("NORTH");
            break;

        case EAST:
            arduboy.print("EAST");
            break;

        case SOUTH:
            arduboy.print("SOUTH");
            break;

        case WEST:
            arduboy.print("WEST");
            break;
        }
    }

    // arduboy.display();
}
