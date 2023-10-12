#include <Adafruit_NeoPixel.h>
#include "Constants.h"
#include "strips.h"


NeoElectrons smallStrip(SMALLNUMPIXELS, SMALLDATA, NEO_GRB + NEO_KHZ800); // Create the small strip object

int outterDataPins[] = {OUTDATA1, OUTDATA2, OUTDATA3};
int innerDataPins[] = {INDATA1, INDATA2};
NeoStrips outterStrips(3, OUTNUMPIXELS, outterDataPins, smallStrip.Color(outerRED, outerGREEN, outerBLUE), smallStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE));
NeoStrips innerStrips(2, INNUMPIXELS, innerDataPins, smallStrip.Color(innerRED, innerGREEN, innerBLUE), smallStrip.Color(innerBACKGROUNDRED, innerBACKGROUNDGREEN, innerBACKGROUNDBLUE));

int innerStripPixelIndex = 0; // the index of the first electron / pixel in the inner strip
int outerStripPixelIndex = 0; // the index of the first electron / pixel in the outer strip
int smallStripPixelIndex = 0; // the index of the first electron / pixel in the small strip
int togetherAmount = 0;

// I will use these variables when changing the amount of pixels that are lit up on each.
int innerPixelAmount = INPIXELAMOUNT;
int outerPixelAmount = INPIXELAMOUNT;
int smallPixelAmount = SMALLPIXELAMOUNT;

// it is set to true because, we start with the two pixels together
bool wasTogether = true; // This is used to check if the two pixels were together in the last iteration, we use this so that we don't increase the togetherAmount every iteration they are together

void setup() {
  Serial.begin(115200); // Start the serial connection
  while (!Serial) { // Wait for the serial connection to be establised.
    if (millis() > 3000) {
      break; // If we don't get a serial connection in 3 seconds, stop waiting.
    }
    delay(100);
  }
  Serial.println("Serial connection established.");
  Serial.println("Setting up strips...");
  setupStrips();
}

void setupStrips() {
  // Setup small strip
  Serial.println("Setting up small strip...");
  smallStrip.setup(BRIGHTNESS);
  Serial.println("Done setting up strips!");
}

void loop() {
  if (innerStripPixelIndex == outerStripPixelIndex) { // If the two pixels are together
    if (!wasTogether) {
      wasTogether = true;
      Serial.print("Wasn't together before, increasing together amount, New together Amount");
      togetherAmount++; // Increase the together amount
      Serial.println(togetherAmount);
    }
  } else if (wasTogether) {
    wasTogether = false; // Reset the wasTogether variable
    Serial.println("Was together before, setting together amount to 0");
  }
  
  if (togetherAmount >= TOGETHERAMOUNT) { // Electron switch to the other side (>= incase error)
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
  smallStrip.moveColorFowardOnce(smallStrip.Color(smallRED, smallGREEN, smallBLUE), smallStrip.Color(smallBACKGROUNDRED, smallBACKGROUNDGREEN, smallBACKGROUNDBLUE), smallPixelAmount);
  innerStrips.moveElectronsFoward();
  outterStrips.moveElectronsFoward();
  Serial.println("Done moving electrons foward!");
  // Increase the pixel indexes
  innerStripPixelIndex++; // Increase the inner strip pixel index by one
  outerStripPixelIndex++; // Increase the outer strip pixel index by one
  smallStripPixelIndex++; // Increase the small strip pixel index by one
  
  if (smallStripPixelIndex > smallStrip.numPixels()) {
    Serial.println("Resetting small strip pixel index");
    smallStripPixelIndex = 0;
  }
}

void blinkAll(int delayTime, int times) {
  for (int i=0; i<times; i++) {
    innerStrips.flushColor(smallStrip.Color(BLINKRED, BLINKGREEN, BLINKBLUE));
    outterStrips.flushColor(smallStrip.Color(BLINKRED, BLINKGREEN, BLINKBLUE));
    delay(delayTime);
    innerStrips.clear();
    outterStrips.clear();
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
