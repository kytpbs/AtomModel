#include <Adafruit_NeoPixel.h>
#include "Constants.h"
#include "strips.h"

NeoElectrons innerStrip(INNUMPIXELS, INDATA, NEO_GRB + NEO_KHZ800, INPIXELSPACE); // Create the inner strip object
NeoElectrons outerStrip(OUTNUMPIXELS, OUTDATA, NEO_GRB + NEO_KHZ800, OUTPIXELSPACE); // Create the outer strip object
NeoElectrons smallStrip(SMALLNUMPIXELS, SMALLDATA, NEO_GRB + NEO_KHZ800, SMALLPIXELSPACE); // Create the small strip object
NeoElectrons innerStrip2(INNUMPIXELS, INDATA2, NEO_GRB + NEO_KHZ800, INPIXELSPACE); // Create the second inner strip object
NeoElectrons outerStrip2(OUTNUMPIXELS, OUTDATA2, NEO_GRB + NEO_KHZ800, OUTPIXELSPACE); // Create the second outer strip object (this will be duplicated in hardware, so it controlls 2 strips)

unsigned long lastSwitchTime = 0; // The last time the pixels switched


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
  // Setup inner strips
  Serial.println("Setting up inner strip0...");
  innerStrip.setup(BRIGHTNESS); // This initializes the strip

  Serial.println("Setting up inner strip2...");
  innerStrip2.setup(BRIGHTNESS);
      
  // Setup outer strip
  Serial.println("Setting up outer strip 0...");
  outerStrip.setup(BRIGHTNESS); // This initializes the strip

  Serial.println("Setting up outer strip 2...");
  outerStrip2.setup(BRIGHTNESS);

  // Setup small strip
  Serial.println("Setting up small strip...");
  smallStrip.setup(BRIGHTNESS); // This initializes the strip
  smallStrip.pixelSpace = SMALLPIXELSPACE; // Set the pixel space
  Serial.println("Done setting up strips!");
}

void loop() {
  if (millis() - lastSwitchTime >= SWITCHTIME * 1000) { // If it has been SWITCHTIME seconds since the last switch
    runSwitch(); // Run the switch
  }

  moveElectronFoward(); // Move The Electrons Foward
  delay(DELAYTIME);
}

void runSwitch() {
  Serial.println("Blinking! as " + String(SWITCHTIME) + " Seconds have passed."); // Print that we are blinking
  lastSwitchTime = millis(); // Set the last switch time to the current time
  blinkAll(BLINKDELAY, BLINKAMOUNT); // Blink the pixels
  togetherAmount = 0; // Reset the together amount
  switchPixel(); // Switch the pixels
  return;
}

/**
 * Moves the red color by one pixel from the back to the front removing the red color from the back
*/
void moveElectronFoward() {
  // Move the electrons foward
  innerStrip.moveColorFowardOnce(innerStrip.Color(innerRED, innerGREEN, innerBLUE), innerStrip.Color(innerBACKGROUNDRED, innerBACKGROUNDGREEN, innerBACKGROUNDBLUE), innerPixelAmount);
  innerStrip2.moveColorFowardOnce(innerStrip.Color(innerRED, innerGREEN, innerBLUE), innerStrip.Color(innerBACKGROUNDRED, innerBACKGROUNDGREEN, innerBACKGROUNDBLUE), innerPixelAmount);
  outerStrip.moveColorFowardOnce(outerStrip.Color(outerRED, outerGREEN, outerBLUE), outerStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE), outerPixelAmount);
  outerStrip2.moveColorFowardOnce(outerStrip.Color(outerRED, outerGREEN, outerBLUE), outerStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE), outerPixelAmount);
  smallStrip.moveColorFowardOnce(smallStrip.Color(smallRED, smallGREEN, smallBLUE), smallStrip.Color(smallBACKGROUNDRED, smallBACKGROUNDGREEN, smallBACKGROUNDBLUE), smallPixelAmount);
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
  if (innerStrip.electronAmount <= outerStrip.electronAmount) {
    innerStrip.increaseElectronAmount();
    outerStrip.decreaseElectronAmount();
  }
  else {
    innerStrip.decreaseElectronAmount();
    outerStrip.increaseElectronAmount();
  }
}
