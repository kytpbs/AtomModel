#include <Adafruit_NeoPixel.h>
#include "strips.h"

void setPixel(Adafruit_NeoPixel *strip, int index, uint32_t color) {
    strip->setPixelColor(index % strip->numPixels(), color);
}

void flushColor(Adafruit_NeoPixel *strip, uint32_t color) {
    strip->fill(color, 0, strip->numPixels());
    strip->show();
}

void moveColorFowardOnce(Adafruit_NeoPixel *strip, uint32_t color, int index, int numPixels) {
    strip->clear();
    for (int i=0; i<numPixels; i++) {
        setPixel(strip, i*2 + index, color);
    }
    setPixel(strip, index, color);
    strip->show();
}
