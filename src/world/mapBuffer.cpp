#include "MapBuffer.hpp"
#include "../common.hpp"
#include <ArduboyFX.h>

#define ADDRESS_PAD 4

static uint16_t map2Dto1D(uint16_t x, uint16_t y, uint8_t width) {
    return (y * width) + x;
}

MapBuffer::MapBuffer() {
    // this->originX = 0;
    // this->originY = 0;
    // for (uint8_t i = 0; i < 6; i++) {
    //     this->map[i] = &this->lines[i];
    // }
    // mapN = 24, mapM = 24;
}

void MapBuffer::shiftUp() {
    // this->originY++;
    // TileLine *temp = this->map[0];
    // for (uint8_t i = 0; i < 5; i++) {
    //     this->map[i] = this->map[i + 1];
    // }
    // this->map[5] = temp;
    // if (originY <= mapN) {
    //     this->loadLine(5, this->originX, this->originY + 5);
    // } else {
    //     for (uint8_t i = 0; i < 10; i++) {
    //         this->map[5]->tiles[i] = 0;
    //     }
    // }
}

void MapBuffer::shiftDown() {
    // this->originY--;
    // TileLine *temp = this->map[5];
    // for (uint8_t i = 5; i > 0; i--) {
    //     this->map[i] = this->map[i - 1];
    // }
    // this->map[0] = temp;
    // if (originY >= 0) {
    //     this->loadLine(0, this->originX, this->originY);
    // } else {
    //     for (uint8_t i = 0; i < 10; i++) {
    //         this->map[0]->tiles[i] = 0;
    //     }
    // }
}

void MapBuffer::shiftLeft() {
    // this->originX++;
    // for (uint8_t i = 0; i < 6; i++) {
    //     for (uint8_t j = 0; j < 9; j++) {
    //         this->map[i]->tiles[j] = this->map[i]->tiles[j + 1];
    //         map[i]->debug[j] = map[i]->debug[j + 1];
    //     }
    //     this->map[i]->tiles[9] = 0;
    // }
    // if (originX + 9 <= mapM) {
    //     loadVLine(9, this->originX + 9, this->originY);
    // } else {
    //     for (uint8_t i = 0; i < 6; i++) {
    //         this->map[i]->tiles[9] = 0;
    //     }
    // }
}

void MapBuffer::shiftRight() {
    // this->originX--;
    // for (uint8_t i = 0; i < 6; i++) {
    //     for (uint8_t j = 9; j > 0; j--) {
    //         this->map[i]->tiles[j] = this->map[i]->tiles[j - 1];
    //         map[i]->debug[j] = map[i]->debug[j - 1];
    //     }
    //     this->map[i]->tiles[0] = 0;
    // }

    // if (originX >= 0) {
    //     loadVLine(0, this->originX, this->originY);
    // } else {
    //     for (uint8_t i = 0; i < 6; i++) {
    //         this->map[i]->tiles[0] = 0;
    //     }
    // }
}

void MapBuffer::initMap(uint24_t addr) {
    FX::seekData(addr);
    this->height = FX::readPendingUInt8();
    this->width = FX::readPendingUInt8();
    this->startX = FX::readPendingUInt8();
    this->startY = FX::readPendingUInt8();
    (void)FX::readEnd();
    this->addr = addr + ADDRESS_PAD;

    this->loadMap(startX, startY);
}

void MapBuffer::loadMap(uint8_t centerX, uint8_t centerY) {
    this->originX = centerX;
    this->originY = centerY;

    for (uint8_t y = 0; y < BUFFER_HEIGHT; y++) {
        for (uint8_t x = 0; x < BUFFER_WIDTH; x++) {
            this->loadCell(x, y, centerX + x - CENTER_X, centerY + y - CENTER_Y);
        }
        // Serial.print("\n");
    }
}

void MapBuffer::loadCell(uint8_t i, uint8_t j, int16_t x, int16_t y) {
    uint16_t dataOffset = map2Dto1D(x, y, width);
    uint8_t offset = dataOffset >> 8;
    uint8_t integer = dataOffset & 0xFF;

    if (x < 0 || y < 0 || x >= width || y >= height) {
        this->buffer[map2Dto1D(i, j, BUFFER_WIDTH)] = 1;
        return;
    }

    // the index is a 16 bit width address but only 8bit width is allowed
    // need to convert 16 bit to 8 bit + offset
    // i.e. 256 -> 1,0 257 -> 1,1
    this->buffer[map2Dto1D(i, j, BUFFER_WIDTH)] = FX::readIndexedUInt8(addr + (offset * 256), integer);

    // Serial.print("Loading cell: ");
    // Serial.print(i);
    // Serial.print(",");
    // Serial.print(j);
    // Serial.print(",");
    // Serial.print(map2Dto1D(i, j, BUFFER_WIDTH));
    // Serial.print(" data index: ");
    // Serial.print(x);
    // Serial.print(",");
    // Serial.print(y);
    // Serial.print(",");
    // Serial.print(width);
    // Serial.print(",");
    // Serial.print(dataOffset);
    // Serial.print(", offset: ");
    // Serial.print(offset);
    // Serial.print(",");
    // Serial.print(integer);
    // Serial.print(",");
    // Serial.print(this->buffer[map2Dto1D(i, j, BUFFER_WIDTH)]);
    // Serial.print("\n");
}

void MapBuffer::loadLine(uint8_t index, uint16_t startX, uint16_t startY) {
    uint16_t dataOffset = startY * width + startX;
    // the index is a 16 bit width address but only 8bit width is allowed
    // need to convert 16 bit to 8 bit + offset
    // i.e. 256 -> 1,0 257 -> 1,1
    uint8_t offset = dataOffset >> 8;
    uint8_t integer = dataOffset & 0xFF;
    uint24_t addr = addr + (offset * 256) + integer * sizeof(uint8_t);
    FX::seekData(addr);
    for (uint8_t i = 0; i < 10; i++) {
        //  this->map[index]->tiles[i] = FX::readPendingUInt8();
        // map[index]->debug[i] = dataOffset;
    }
    (void)FX::readEnd();
}

void MapBuffer::loadVLine(uint8_t index, uint16_t startX, uint16_t startY) {
    for (uint8_t i = 0; i < 6; i++) {
        uint16_t dataOffset = (startY + i) * width + startX;
        // the index is a 16 bit width address but only 8bit width is allowed
        // need to convert 16 bit to 8 bit + offset
        // i.e. 256 -> 1,0 257 -> 1,1
        uint8_t offset = dataOffset >> 8;
        uint8_t integer = dataOffset & 0xFF;
        uint24_t addr = addr + (offset * 256) + (integer + width) * sizeof(uint8_t);
        this->buffer[map2Dto1D(index, i, width)] = FX::readIndexedUInt8(addr + (offset * 256), integer);
        // map[i]->debug[index] = dataOffset;
    }
}

void MapBuffer::draw() {
    Arduboy2::drawRect(17, 17, BUFFER_WIDTH * 4 + 4, BUFFER_HEIGHT * 4 + 4, WHITE);
    Arduboy2::fillRect(18, 18, BUFFER_WIDTH * 4 + 2, BUFFER_HEIGHT * 4 + 2, BLACK);
    for (uint8_t y = 0; y < BUFFER_HEIGHT; y++) {
        for (uint8_t x = 0; x < BUFFER_WIDTH; x++) {
            uint8_t tile = this->buffer[map2Dto1D(x, y, BUFFER_WIDTH)];

            if (tile == 0) {
                Arduboy2Base::fillRect(20 + ((BUFFER_WIDTH - x - 1) * 4), 20 + (y * 4), 3, 3, WHITE);
            }

            if (x == CENTER_X && y == CENTER_Y) {
                Arduboy2Base::drawPixel(20 + ((BUFFER_WIDTH - x - 1) * 4) + 1, 20 + (y * 4) + 1, BLACK);
            }
        }
    }
}