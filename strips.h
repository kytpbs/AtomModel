#ifndef STRIPS_H
#define STRIPS_H

#include <Adafruit_NeoPixel.h>

void flushColor(Adafruit_NeoPixel *strip, uint32_t color);
void blink(Adafruit_NeoPixel *strip, int delayTime, int times);
void moveColorFowardOnce(Adafruit_NeoPixel *strip, uint32_t color, int index);

#endif
