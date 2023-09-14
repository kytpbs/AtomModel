#include <Adafruit_NeoPixel.h>
#include "pinConstants.h"

Adafruit_NeoPixel lowerPixels[lengthLower];
Adafruit_NeoPixel upperPixels[lengthUpper];

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    // Wait for serial monitor to open
    while(!Serial) { 
        delay(100);
        if (millis() > 5000) {
          // If serial monitor doesn't open, continue anyway.
          break;
        }
    }
    Serial.println("Serial monitor opened");
    Serial.println("Initializing NeoPixels");
    // Initialize NeoPixels
    setupStrips();
}

void setupStrips() {
  for (int i = 0; i < lengthLower; i++) {
      Serial.print("Initializing lower strip on pin: ");
      Serial.println(lowerLedPins[i]);
      Adafruit_NeoPixel lowerPixel = Adafruit_NeoPixel(DOWNNUMPIXELS, lowerLedPins[i], NEO_GRB + NEO_KHZ800);
      lowerPixel.begin();
      lowerPixels[i] = lowerPixel;
    }
    // Upper strip
    for (int i = 0; i < lengthUpper; i++) {
      Serial.print("Initializing upper strip on pin: ");
      Serial.println(upperLedPins[i]);
      Adafruit_NeoPixel upperPixel = Adafruit_NeoPixel(UPNUMPIXELS, upperLedPins[i], NEO_GRB + NEO_KHZ800);
      upperPixel.begin();
      upperPixels[i] = upperPixel;
    }

}

void loop() {
  // put your main code here, to run repeatedly:
  blink(100, 1);
}

/**
 * Moves the red color pixel by pixel from the back to the front removing the red color from the back
*/
void moveRedFowards(int waitTime) {
  int loop_amount = max(lengthLower, lengthUpper); //the Higher amount of strips so that we can loop over all of them at the same time
  for (int i = 0; i < loop_amount; i++) {
    for (int j = 0; j < UPNUMPIXELS; j++) {
      if (i < lengthLower) {
        lowerPixels[i].setPixelColor(j, Adafruit_NeoPixel::Color(255, 0, 0)); // Red
      }
      if (i < lengthUpper) {
        upperPixels[i].setPixelColor(j, Adafruit_NeoPixel::Color(255, 0, 0)); // Red
      }
      if (j <= 0) {
        lowerPixels[i].show();
        upperPixels[i].show();
        continue;
      }
      delay(waitTime);
      if (i < lengthLower) {
        lowerPixels[i].setPixelColor(j - 1, Adafruit_NeoPixel::Color(0, 0, 0)); // Black
        lowerPixels[i].show();
      }
      if (i < lengthUpper) {
        upperPixels[i].setPixelColor(j - 1, Adafruit_NeoPixel::Color(0, 0, 0)); // Black
        upperPixels[i].show();
      }
    }
  }
}

void blink(int delayTime, int times) {
  for (int i = 0; i < times; i++) {
    Serial.println("Blinking");
    // Turn on all LEDs
    int loop_amount = max(lengthLower, lengthUpper); //the Higher amount of strips so that we can loop over all of them at the same time
    for (int i = 0; i < loop_amount; i++) {
      if (i < lengthLower) {
        lowerPixels[i].fill(Adafruit_NeoPixel::Color(255, 0, 0)); // Red
        lowerPixels[i].show();
      }
      if (i < lengthUpper) {
        upperPixels[i].fill(Adafruit_NeoPixel::Color(255, 0, 0)); // Red
        upperPixels[i].show();
      }
    }
    // Wait
    delay(delayTime);
    // Turn off all LEDs
    for (int i = 0; i < loop_amount; i++) {
      if (i < lengthLower) {
        lowerPixels[i].clear(); // Clear all pixels -> turn off all LEDs
        lowerPixels[i].show(); // Update the strip
      }
      if (i < lengthUpper) {
        upperPixels[i].clear(); // Clear all pixels -> turn off all LEDs
        upperPixels[i].show(); // Update the strip
      }
    }
    delay(delayTime);
  }
}
