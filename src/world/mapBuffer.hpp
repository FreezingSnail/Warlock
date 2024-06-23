#pragma once
#include <stdint.h>
#include "../lib/uint24.h"
#define BUFFER_WIDTH 9
#define BUFFER_HEIGHT 9
#define CENTER_X 4
#define CENTER_Y 4

/*

 buffer is 8x8 tiles
 we want to keep the player centered, so the player
 will always have the longest possible view in the buffer
 as the buffer is 8x8, we cant be in the true center
 so we will set the center to 3,3

    0 1 2 3 4 5 6 7
    1
    2
    3     x0
    4     00
    5
    6
    7


when the map shifts, the player never leaves the 3,3 tile as it is the enter of the world
so when the buffer if shifted, the player needs to be shifted back to 3,3

*/

class MapBuffer {
  public:
    uint8_t buffer[BUFFER_HEIGHT * BUFFER_WIDTH];
    uint16_t debug[8 * 8];
    uint8_t originX, originY;
    uint8_t startX, startY;
    uint8_t height, width;
    uint24_t addr;

    MapBuffer();
    void shiftUp();
    void shiftDown();
    void shiftLeft();
    void shiftRight();

    void initMap(uint24_t addr);
    void loadMap(uint8_t topX, uint8_t topY);
    void loadLine(uint8_t index, uint16_t startX, uint16_t startY);
    void loadVLine(uint8_t index, uint16_t startX, uint16_t startY);
    void loadCell(uint8_t i, uint8_t j, int16_t x, int16_t y);

    void draw();
};