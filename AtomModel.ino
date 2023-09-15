#include <Adafruit_NeoPixel.h>
#include "pinConstants.h"
#include "strips.h"

//Adafruit_NeoPixel loverStrip(UPNUMPIXELS, UPDATA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel loverStrip(UPNUMPIXELS, UPDATA, NEO_GBR + NEO_KHZ800);
// Adafruit_NeoPixel upperStrip(DOWNNUMPIXELS, DOWNDATA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel upperStrip(DOWNNUMPIXELS, DOWNDATA, NEO_GRB + NEO_KHZ800);

int strip1Index = 0;
int strip2Index = 0;
int togetherAmount = 0;

// I will use these variables when changing the amount of pixels that are lit up on each.
int loverPixelAmount = 2;
int upperPixelAmount = 2;

bool wasTogether = true;

void setup() {
  Serial.begin(115200);
  while (!Serial) { // Wait for the serial connection to be establised.
    if (millis() > 4000) {
      break; // If we don't get a serial connection in 4 seconds, stop waiting.
    }
  }
  Serial.println("Serial connection established.");
  Serial.println("Setting up strips...");
  setupStrips();
}

void setupStrips() {
  // Setup lover strip
  Serial.println("Setting up lover strip...");
  loverStrip.begin();
  loverStrip.show(); // Initialize all pixels to 'off'
  
  // Setup upper strip
  Serial.println("Setting up upper strip...");
  upperStrip.begin();
  upperStrip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (strip1Index == strip2Index) {
    if (!wasTogether) {
      wasTogether = true;
      Serial.println("Wasn't together before, increasing together amount");
      togetherAmount++;
    }
  }
  else {
    if (wasTogether) {
      wasTogether = false;
      Serial.println("Was together before, setting together amount to 0");
    }
  }
  
  if (togetherAmount > 5) {
    Serial.println("Blinking! as they were together for 5 times");
    blinkAll(100, 3);
    togetherAmount = 0;
    delay(500);
    switchPixel();
    return;
  }

  moveRedFowards();
  delay(200);
}

/**
 * Moves the red color pixel by pixel from the back to the front removing the red color from the back
*/
void moveRedFowards() {
  moveColorFowardOnce(&loverStrip, loverStrip.Color(255, 0, 0), strip1Index, loverPixelAmount);
  moveColorFowardOnce(&upperStrip, upperStrip.Color(255, 0, 0), strip2Index, upperPixelAmount);
  strip1Index++;
  strip2Index++;
  if (strip1Index >= loverStrip.numPixels()) {
    strip1Index = 0;
  }
  if (strip2Index >= upperStrip.numPixels()) {
    strip2Index = 0;
  }
}

void blinkAll(int delayTime, int times) {
  for (int i=0; i<times; i++) {
    flushColor(&loverStrip, loverStrip.Color(255, 0, 0));
    flushColor(&upperStrip, upperStrip.Color(255, 0, 0));
    delay(delayTime);
    loverStrip.clear();
    loverStrip.show();
    upperStrip.clear();
    upperStrip.show();
    delay(delayTime);
  }
}

void switchPixel() {
  if (loverPixelAmount == upperPixelAmount) {
    loverPixelAmount += 1;
    upperPixelAmount -= 1;
  }
  else if (loverPixelAmount > upperPixelAmount) {
    loverPixelAmount -= 1;
    upperPixelAmount += 1;
  }
  else if (loverPixelAmount < upperPixelAmount) {
    loverPixelAmount += 1;
    upperPixelAmount -= 1;
  }
  else {
    Serial.println("Something went wrong, loverPixelAmount and upperPixelAmount are not equal, but none of the if statements were true");
  }
}
