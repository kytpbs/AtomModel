#include <Adafruit_NeoPixel.h>
#include "Constants.h"
#include "strips.h"

Adafruit_NeoPixel loverStrip(UPNUMPIXELS, UPDATA, NEO_GRB + NEO_KHZ800); // Create the lover strip object
Adafruit_NeoPixel upperStrip(DOWNNUMPIXELS, DOWNDATA, NEO_GRB + NEO_KHZ800); // Create the upper strip object

int loverStripPixelIndex = 0; // the index of the first electron / pixel in the lover strip
int upperStripPixelIndex = 0; // the index of the first electron / pixel in the upper strip
int togetherAmount = 0;

// I will use these variables when changing the amount of pixels that are lit up on each.
int loverPixelAmount = PIXELAMOUNT;
int upperPixelAmount = PIXELAMOUNT;

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
  // Setup lover strip
  Serial.println("Setting up lover strip...");
  loverStrip.begin(); // This initializes the strip
  loverStrip.setBrightness(BRIGHTNESS); // Set the brightness of the strip
  loverStrip.clear(); // Set all pixel colors to 'off'
  loverStrip.show(); // Initialize all pixels to 'off'
  
  // Setup upper strip
  Serial.println("Setting up upper strip...");
  upperStrip.begin(); // This initializes the strip
  upperStrip.setBrightness(BRIGHTNESS); // Set the brightness of the strip
  upperStrip.clear(); // Set all pixel colors to 'off'
  upperStrip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (loverStripPixelIndex == upperStripPixelIndex) { // If the two pixels are together
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

  moveRedFowards(); // Move The Electrons Foward
  delay(DELAYTIME);
}

/**
 * Moves the red color by one pixel from the back to the front removing the red color from the back
*/
void moveRedFowards() {
  moveColorFowardOnce(&loverStrip, loverStrip.Color(RED, GREEN, BLUE), loverStripPixelIndex, loverPixelAmount);
  moveColorFowardOnce(&upperStrip, upperStrip.Color(RED, GREEN, BLUE), upperStripPixelIndex, upperPixelAmount);
  loverStripPixelIndex++;
  upperStripPixelIndex++;
  if (loverStripPixelIndex >= loverStrip.numPixels()) {
    loverStripPixelIndex = 0;
  }
  if (upperStripPixelIndex >= upperStrip.numPixels()) {
    upperStripPixelIndex = 0;
  }
}

void blinkAll(int delayTime, int times) {
  for (int i=0; i<times; i++) {
    flushColor(&loverStrip, loverStrip.Color(BLINKRED, BLINKGREEN, BLINKBLUE));
    flushColor(&upperStrip, upperStrip.Color(BLINKRED, BLINKGREEN, BLINKBLUE));
    delay(delayTime);
    loverStrip.clear();
    upperStrip.clear();
    loverStrip.show();
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
