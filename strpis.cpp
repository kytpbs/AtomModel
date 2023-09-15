#include <Adafruit_NeoPixel.h>
#include "strips.h"



void flushColor(Adafruit_NeoPixel *strip, uint32_t color) {
  for(int i=0; i<strip->numPixels(); i++) { // For each pixel in strip...
    strip->setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip->show();                          //  Update strip to match
  }
}

void blink(Adafruit_NeoPixel *strip, int delayTime, int times) {
  for(int i=0; i<times; i++) {
    flushColor(strip, strip->Color(255, 0, 0));
    delay(delayTime);
    flushColor(strip, strip->Color(0, 0, 0));
    delay(delayTime);
  }
}

/**
 * Moves the red color pixel by pixel from the back to the front removing the red color from the back
 * INDEX: The index of the pixel to light up
*/
void moveColorFowardOnce(Adafruit_NeoPixel *strip, uint32_t color, int index) {
    strip->clear();
    strip->setPixelColor(index, color);
    strip->show();
}
