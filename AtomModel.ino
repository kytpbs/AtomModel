#include <Adafruit_NeoPixel.h>
#include "Constants.h"
#include "strips.h"

Adafruit_NeoPixel innerStrip(OUTNUMPIXELS, OUTDATA, NEO_GRB + NEO_KHZ800); // Create the inner strip object
Adafruit_NeoPixel outerStrip(INNUMPIXELS, INDATA, NEO_GRB + NEO_KHZ800); // Create the outer strip object

int innerStripPixelIndex = 0; // the index of the first electron / pixel in the inner strip
int outerStripPixelIndex = 0; // the index of the first electron / pixel in the outer strip
int togetherAmount = 0;

// I will use these variables when changing the amount of pixels that are lit up on each.
int innerPixelAmount = PIXELAMOUNT;
int outerPixelAmount = PIXELAMOUNT;

// it is set to true because, we start with the two pixels together
bool wasTogether = true; // This is used to check if the two pixels were together in the last iteration, we use this so that we don't increase the togetherAmount every iteration they are together

void setup() {
  Serial.begin(115200); // Start the serial connection
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
  // Setup inner strip
  Serial.println("Setting up inner strip...");
  innerStrip.begin(); // This initializes the strip
  innerStrip.setBrightness(BRIGHTNESS); // Set the brightness of the strip
  innerStrip.clear(); // Set all pixel colors to 'off'
  innerStrip.show(); // Initialize all pixels to 'off'
  
  // Setup outer strip
  Serial.println("Setting up outer strip...");
  outerStrip.begin(); // This initializes the strip
  outerStrip.setBrightness(BRIGHTNESS); // Set the brightness of the strip
  outerStrip.clear(); // Set all pixel colors to 'off'
  outerStrip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (innerStripPixelIndex == outerStripPixelIndex) { // If the two pixels are together
    if (!wasTogether) {
      wasTogether = true;
      Serial.print("Wasn't together before, increasing together amount, New together Amount");
      togetherAmount++;
      Serial.println(togetherAmount);
    }
  } else if (wasTogether) {
    wasTogether = false; // Reset the wasTogether variable
    Serial.println("Was together before, setting together amount to 0");
  }
  
  
  if (togetherAmount >= TOGETHERAMOUNT) { // Electron switch to the other side
    Serial.println("Blinking! as they were together for 5 times");
    blinkAll(BLINKDELAY, BLINKAMOUNT); // Blink the pixels
    togetherAmount = 0; // Reset the together amount
    switchPixel(); // Switch the pixels
    return;
  }

  moveElectronFoward(); // Move The Electrons Foward
  delay(DELAYTIME);
}

/**
 * Moves the red color by one pixel from the back to the front removing the red color from the back
*/
void moveElectronFoward() {
  moveColorFowardOnce(&innerStrip, innerStrip.Color(innerRED, innerGREEN, innerBLUE), innerStrip.Color(innerBACKGROUNDRED, innerBACKGROUNDGREEN, innerBACKGROUNDBLUE), innerStripPixelIndex, innerPixelAmount);
  moveColorFowardOnce(&outerStrip, outerStrip.Color(outerRED, outerGREEN, outerBLUE), outerStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE), outerStripPixelIndex, outerPixelAmount);
  innerStripPixelIndex++;
  outerStripPixelIndex++;
  if (innerStripPixelIndex > innerStrip.numPixels()) {
    innerStripPixelIndex = 0;
  }
  if (outerStripPixelIndex > outerStrip.numPixels()) {
    outerStripPixelIndex = 0;
  }
}

void blinkAll(int delayTime, int times) {
  for (int i=0; i<times; i++) {
    flushColor(&innerStrip, innerStrip.Color(BLINKRED, BLINKGREEN, BLINKBLUE));
    flushColor(&outerStrip, outerStrip.Color(BLINKRED, BLINKGREEN, BLINKBLUE));
    delay(delayTime);
    innerStrip.clear();
    outerStrip.clear();
    innerStrip.show();
    outerStrip.show();
    delay(delayTime);
  }
}

void switchPixel() {
  if (innerPixelAmount <= outerPixelAmount) {
    innerPixelAmount += 1;
    outerPixelAmount -= 1;
  }
  else {
    innerPixelAmount -= 1;
    outerPixelAmount += 1;
  }
}
