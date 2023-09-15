#include <Adafruit_NeoPixel.h>
#include "strips.h"

void setPixel(Adafruit_NeoPixel *strip, int index, uint32_t color) {
    strip->setPixelColor(index % strip->numPixels(), color);
}

void flushColor(Adafruit_NeoPixel *strip, uint32_t color) {
    strip->fill(color, 0, strip->numPixels());
    strip->show();
}

void blink(Adafruit_NeoPixel *strip, int delayTime, int times) {
  for(int i=0; i<times; i++) {
    flushColor(strip, strip->Color(255, 0, 0));
    delay(delayTime);
    flushColor(strip, strip->Color(0, 0, 0));
    delay(delayTime);
  }
}

void moveColorFowardOnce(Adafruit_NeoPixel *strip, uint32_t color, int index, int numPixels) {
    strip->clear();
    for (int i=0; i<numPixels; i++) {
        setPixel(strip, i*2 + index, color);
    }
    setPixel(strip, index, color);
    strip->show();
}
