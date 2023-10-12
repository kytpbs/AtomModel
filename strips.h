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

class NeoElectrons: public Adafruit_NeoPixel{
    public:
        uint32_t electronColor;
        uint32_t backgroundColor;
        int pixelSpace;
        int electronAmount;
        int electronIndex;
        NeoElectrons();
        NeoElectrons(uint16_t n, int16_t p, neoPixelType t);
        NeoElectrons(uint16_t n, int16_t p);
        void setup();
        void setup(int brightness);
        /**
         * Sets the pixel at the given index to the given color
         * Uses circular indexing, so if the index is greater than the number of pixels, it will wrap around
         * Will not show the pixel unlike other functions. You must call strip.show() after calling this function
        */
        void setPixel(int index, uint32_t color);
        /**
         * Sets all the pixels to the given color
         * It will show the pixels unlike the setPixel function
         * @param STRIP: The strip to change the pixels of
         * @param COLOR: The color to set the pixels to
        */
        void flushColor(uint32_t color);
        /**
         * Sets the colors of the electron and the background
        */
        void setColors(uint32_t electronColor, uint32_t backgroundColor);
        /**
         * Moves the electron foward once one pixel from the index
         * Call this function periodically to move the electron foward
         * @return The Index of the first electron
        */
        int moveColorFowardOnce(uint32_t color, uint32_t backgroundColor, int pixelAmount);
        /**
         * Moves the electron foward once one pixel from the index
         * Call this function periodically to move the electron foward
         * @return The Index of the first electron
        */
        int moveColorFowardOnce(uint32_t color, uint32_t backgroundColor);
        /**
         * Moves the electron foward once one pixel from the index
         * Call this function periodically to move the electron foward
         * @return The Index of the first electron 
        */
        int moveColorFowardOnce();
};

class NeoStrips {
    private:
        int stripAmount;
        NeoElectrons* stripsArray;
        int* electronIndexArray;
    
    public:
        NeoStrips(int stripAmount, int pixelAmount, int* stripPins, uint32_t electronColor, uint32_t backgroundColor);
        NeoStrips(int stripAmount, int* pixelAmounts, int* stripPins, uint32_t* electronColors, uint32_t* backgroundColors);
        void blink();
        void blink(unsigned int times);
        void moveElectronsFoward();
        bool areElectronsTogether(int strip1, int strip2);
};

#endif
