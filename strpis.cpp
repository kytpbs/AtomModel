#include <Adafruit_NeoPixel.h>
#include "strips.h"
#include "Constants.h"

void setPixel(Adafruit_NeoPixel *strip, int index, uint32_t color) {
    strip->setPixelColor(index % strip->numPixels(), color);
}

void flushColor(Adafruit_NeoPixel *strip, uint32_t color) {
    strip->fill(color, 0, strip->numPixels());
    strip->show();
}

void moveColorFowardOnce(Adafruit_NeoPixel *strip, uint32_t color, uint32_t backgroundColor, int index, int numPixels) {
    strip->clear(); // Clear the strip
    strip->fill(backgroundColor, 0); // Set the background color
    for (int i=0; i<numPixels; i++) {
      setPixel(strip, i*PIXELSPACE + index, color);
    }
    strip->show();
}
