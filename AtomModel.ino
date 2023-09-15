#include <Adafruit_NeoPixel.h>
#include "pinConstants.h"
#include "strips.h"

// TODO: Add support for multiple pixels on the same strip

//Adafruit_NeoPixel loverStrip(UPNUMPIXELS, UPDATA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel loverStrip(UPNUMPIXELS, UPDATA, NEO_GBR + NEO_KHZ800);
// Adafruit_NeoPixel upperStrip(DOWNNUMPIXELS, DOWNDATA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel upperStrip(DOWNNUMPIXELS, DOWNDATA, NEO_GRB + NEO_KHZ800);

int strip1Index = 0;
int strip2Index = 0;
int togetherAmount = 0;
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
    Serial.println("Together!");
    togetherAmount++;
  }
  
  if (togetherAmount > 5) {
    Serial.println("Blinking! as they were together for 5 times");
    blinkAll(100, 3);
    togetherAmount = 0;
    delay(500);
    // TODO: do the bit shift thingy
    return;
  }

  moveRedFowards();
  delay(200);
}

/**
 * Moves the red color pixel by pixel from the back to the front removing the red color from the back
*/
void moveRedFowards() {
  moveColorFowardOnce(&loverStrip, loverStrip.Color(255, 0, 0), strip1Index);
  moveColorFowardOnce(&upperStrip, upperStrip.Color(255, 0, 0), strip2Index);
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
