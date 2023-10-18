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
  innerStrip.setColors(innerStrip.Color(innerRED, innerGREEN, innerBLUE), innerStrip.Color(innerBACKGROUNDRED, innerBACKGROUNDGREEN, innerBACKGROUNDBLUE)); // Set the colors of the strip
  innerStrip.setElectronAmont(INPIXELAMOUNT); // Set the amount of electrons in the strip

  Serial.println("Setting up inner strip2...");
  innerStrip2.setup(BRIGHTNESS);
  innerStrip2.setColors(innerStrip.Color(innerRED, innerGREEN, innerBLUE), innerStrip.Color(innerBACKGROUNDRED, innerBACKGROUNDGREEN, innerBACKGROUNDBLUE)); // Set the colors of the strip
  innerStrip2.setElectronAmont(INPIXELAMOUNT); // Set the amount of electrons in the strip

  // Setup outer strip
  Serial.println("Setting up outer strip 0...");
  outerStrip.setup(BRIGHTNESS); // This initializes the strip
  outerStrip.setColors(outerStrip.Color(outerRED, outerGREEN, outerBLUE), outerStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE)); // Set the colors of the strip
  outerStrip.setElectronAmont(OUTPIXELAMOUNT); // Set the amount of electrons in the strip

  Serial.println("Setting up outer strip 2...");
  outerStrip2.setup(BRIGHTNESS);
  outerStrip2.setColors(outerStrip.Color(outerRED, outerGREEN, outerBLUE), outerStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE)); // Set the colors of the strip
  outerStrip2.setElectronAmont(OUTPIXELAMOUNT); // Set the amount of electrons in the strip

  // Setup small strip
  Serial.println("Setting up small strip...");
  smallStrip.setup(BRIGHTNESS); // This initializes the strip
  smallStrip.setColors(smallStrip.Color(smallRED, smallGREEN, smallBLUE), smallStrip.Color(smallBACKGROUNDRED, smallBACKGROUNDGREEN, smallBACKGROUNDBLUE)); // Set the colors of the strip
  smallStrip.setElectronAmont(SMALLPIXELAMOUNT); // Set the amount of electrons in the strip
  Serial.println("Done setting up strips!");
}

void loop() {
  if (millis() - lastSwitchTime >= SWITCHTIME * 1000) { // If it has been SWITCHTIME seconds since the last switch
    runSwitch(); // Run the switch
  }

  moveElectronFoward(); // Move The Electrons Foward
  updateBlinks(); // Run the updateBlink function for all the strips
  delay(DELAYTIME);
}

void runSwitch() {
  Serial.println("Blinking! as " + String(SWITCHTIME) + " Seconds have passed."); // Print that we are blinking
  lastSwitchTime = millis(); // Set the last switch time to the current time
  blinkAll(BLINKAMOUNT); // Blink the pixels
  switchPixel(); // Switch the pixels
  return;
}

/**
 * Moves the red color by one pixel from the back to the front removing the red color from the back
*/
void moveElectronFoward() {
  // Move the electrons foward
  innerStrip.moveColorFowardOnce();
  innerStrip2.moveColorFowardOnce();
  outerStrip.moveColorFowardOnce();
  outerStrip2.moveColorFowardOnce();
  smallStrip.moveColorFowardOnce();
}

void updateBlinks() {
  innerStrip.updateBlink();
  innerStrip2.updateBlink();
  outerStrip.updateBlink();
  outerStrip2.updateBlink();
  smallStrip.updateBlink();
}

void blinkAll(int times) {
  innerStrip.startBlink(times);
  outerStrip.startBlink(times);
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
