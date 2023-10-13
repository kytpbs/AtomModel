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

void moveColorFowardOnceLib(Adafruit_NeoPixel *strip, uint32_t color, uint32_t backgroundColor, int index, int numPixels, int pixelSpace) {
    strip->clear(); // Clear the strip
    strip->fill(backgroundColor, 0); // Set the background color
    for (int i=0; i<numPixels; i++) {
      setPixel(strip, i*pixelSpace + index, color);
    }
    strip->show();
}


/* ELECTRONS CLASS */
NeoElectrons::NeoElectrons(): Adafruit_NeoPixel() {
    this->pixelSpace = DEFAULTPIXELSPACE;
}

NeoElectrons::NeoElectrons(uint16_t n, int16_t p, neoPixelType t): Adafruit_NeoPixel(n, p, t) {
    this->pixelSpace = DEFAULTPIXELSPACE;
}

NeoElectrons::NeoElectrons(uint16_t n, int16_t p): Adafruit_NeoPixel(n, p) {
    this->pixelSpace = DEFAULTPIXELSPACE;
}

NeoElectrons::NeoElectrons(uint16_t n, int16_t p, neoPixelType t, int pixelSpace): Adafruit_NeoPixel(n, p, t) {
    this->pixelSpace = pixelSpace;
}

NeoElectrons::NeoElectrons(uint16_t n, int16_t p, int pixelSpace): Adafruit_NeoPixel(n, p) {
    this->pixelSpace = pixelSpace;
}

void NeoElectrons::setup(int brightness) {
    this->begin(); // This initializes the strip
    this->setBrightness(brightness); // Set the brightness of the strip
    this->clear(); // Set all pixel colors to 'off'
    this->show(); // Initialize all pixels to 'off'
}

void NeoElectrons::setup() {
    setup(BRIGHTNESS);
}

void NeoElectrons::setPixel(int index, uint32_t color) {
    setPixelColor(index % numPixels(), color);
}

void NeoElectrons::flushColor(uint32_t color) {
    fill(color, 0, numPixels());
    show();
}

int NeoElectrons::moveColorFowardOnce(uint32_t color, uint32_t backgroundColor, int activePixelAmount) {
    moveColorFowardOnceLib(this, color, backgroundColor, electronIndex, activePixelAmount, pixelSpace);
    this->electronIndex++;
    if (electronIndex >= numPixels()) {
        electronIndex = 0;
    }
    return electronIndex;
}

int NeoElectrons::moveColorFowardOnce(uint32_t color, uint32_t backgroundColor) {
    return moveColorFowardOnce(color, backgroundColor, electronAmount);
}

int NeoElectrons::moveColorFowardOnce() {
    return moveColorFowardOnce(electronColor, backgroundColor);
}

void NeoElectrons::setColors(uint32_t electronColor, uint32_t backgroundColor) {
    this->electronColor = electronColor;
    this->backgroundColor = backgroundColor;
}

/* NEO STRIPS CLASS*/
NeoStrips::NeoStrips(int stripAmount, int* pixelAmounts, int* stripPins, uint32_t* electronColors, uint32_t* backgroundColors) {
    this->stripAmount = stripAmount;
    stripsArray = new NeoElectrons[stripAmount];
    electronIndexArray = new int[stripAmount];
    for (int i=0; i<stripAmount; i++) {
        stripsArray[i] = NeoElectrons(pixelAmounts[i], stripPins[i]);
        stripsArray[i].setColors(electronColors[i], backgroundColors[i]);
        stripsArray[i].setup();
    }
}

NeoStrips::NeoStrips(int stripAmount, int pixelAmount, int* stripPins, uint32_t electronColor, uint32_t backgroundColor) {
    this->stripAmount = stripAmount;
    stripsArray = new NeoElectrons[stripAmount];
    electronIndexArray = new int[stripAmount];
    for (int i=0; i<stripAmount; i++) {
        stripsArray[i] = NeoElectrons(pixelAmount, stripPins[i]);
        stripsArray[i].setColors(electronColor, backgroundColor);
        stripsArray[i].setup();
    }
}

void NeoStrips::moveElectronsFoward() {
    for (int i=0; i<stripAmount; i++) {
        electronIndexArray[i] = stripsArray[i].moveColorFowardOnce();
    }
}

void NeoStrips::flushColor(uint32_t color) {
    for (int i=0; i<stripAmount; i++) {
        stripsArray[i].flushColor(color);
        stripsArray[i].show();
    }
}

void NeoStrips::clear() {
    for (int i=0; i<stripAmount; i++) {
        stripsArray[i].clear();
        stripsArray[i].show();
    }
}

void NeoStrips::blink() {
    for (int i=0; i<stripAmount; i++) {
        stripsArray[i].flushColor(stripsArray[i].electronColor);
    }
    delay(BLINKDELAY);
    for (int i=0; i<stripAmount; i++) {
        stripsArray[i].flushColor(stripsArray[i].backgroundColor);
    }
    delay(BLINKDELAY);
}

void NeoStrips::blink(unsigned int times) {
    for (int i=0; i<times; i++) {
        blink();
    }
}

bool NeoStrips::areElectronsTogether(int strip1Index, int strip2Index) {
    return this->getStripElectronIndex(strip1Index) == this->getStripElectronIndex(strip2Index);
}

int NeoStrips::getStripElectronIndex(int stripIndex) {
    return stripsArray[stripIndex].getElectronIndex();
}
