#ifndef STRIPS_H
#define STRIPS_H

#include <Adafruit_NeoPixel.h>

/**
 * Sets the pixel at the given index to the given color
 * Uses circular indexing, so if the index is greater than the number of pixels, it will wrap around
 * Will not show the pixel unlike other functions. You must call strip.show() after calling this function
*/
void setPixel(Adafruit_NeoPixel *strip, int index, uint32_t color);

/**
 * Sets all the pixels to the given color
 * It will show the pixels unlike the setPixel function
 * @param STRIP: The strip to change the pixels of
 * @param COLOR: The color to set the pixels to
*/
void flushColor(Adafruit_NeoPixel *strip, uint32_t color);

/**
 * Moves the red color pixel by pixel from the back to the front removing the red color from the back
 * @param INDEX: The index of the pixel to light up
 * @param NUMPIXELS: The number of pixels in the strip will be used to wrap around the index, will leave an empty between them (might change later, should I?)
*/
void moveColorFowardOnce(Adafruit_NeoPixel *strip, uint32_t color, uint32_t backgroundColor, int index, int numPixels);

#endif
