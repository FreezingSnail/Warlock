#include <ArduboyFX.h>
#include "src/fxdata.h"
Arduboy2 arduboy;

void setup() {
    arduboy.begin();
    arduboy.initRandomSeed();

    FX::begin(FX_DATA_PAGE);
    // FX::setFont(ArduFont, dcmNormal);   // select default font
    FX::setCursorRange(0, 32767);

}

void run() {

    
}

void render() {
    arduboy.clear();
    arduboy.display();
   
}

void loop() {
    if(!arduboy.nextFrame())
     return;

    run();
    render();
}
