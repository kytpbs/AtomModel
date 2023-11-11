#include "Constants.h"
#include "strips.h"

#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266) // only include if we are on an ESP
#include "thingProperties.h"
#endif

#ifdef ARDUINO_ARCH_ESP8266
unsigned long lastCloudUpdate = 0;
#endif

NeoElectrons smallStrip(SMALLNUMPIXELS, SMALLDATA, NEO_GRB + NEO_KHZ800); // Create the small strip object
NeoElectrons innerStrip(INNUMPIXELS, INDATA, NEO_GRB + NEO_KHZ800); // Create the inner strip object
NeoElectrons innerStrip2(INNUMPIXELS, INDATA2, NEO_GRB + NEO_KHZ800); // Create the second inner strip object
NeoElectrons outerStrip(OUTNUMPIXELS, OUTDATA, NEO_GRB + NEO_KHZ800); // Create the outer strip object
NeoElectrons outerStrip2(OUTNUMPIXELS, OUTDATA2, NEO_GRB + NEO_KHZ800); // Create the second outer strip object
NeoElectrons outerStrip3(OUTNUMPIXELS, OUTDATA3, NEO_GRB + NEO_KHZ800); // Create the third outer strip object

unsigned long lastSwitchTime = 0; // The last time the pixels switched

bool builtinLedState = false; // The state of the builtin led


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

#ifdef ARDUINO_ARCH_ESP32
  Serial.println("On ESP, ENABLING CLOUD");
  cloudSetup();
#elif defined(ARDUINO_ARCH_ESP8266)
  Serial.println("On ESP8266, ENABLING CLOUD (in main loop)");
  cloudSetup();
#else
  Serial.println("On Unknown, NOT ENABLING CLOUD");
#endif
}


void setupStrips() {
  // Setup inner strips
  Serial.println("Setting up inner strip1...");
  innerStrip.setup(BRIGHTNESS); // This initializes the strip
  innerStrip.setColors(innerStrip.Color(innerRED, innerGREEN, innerBLUE), innerStrip.Color(innerBACKGROUNDRED, innerBACKGROUNDGREEN, innerBACKGROUNDBLUE)); // Set the colors of the strip
  innerStrip.setElectronAmont(INPIXELAMOUNT); // Set the amount of electrons in the strip

  Serial.println("Setting up inner strip2...");
  innerStrip2.setup(BRIGHTNESS);
  innerStrip2.setColors(innerStrip.Color(innerRED, innerGREEN, innerBLUE), innerStrip.Color(innerBACKGROUNDRED, innerBACKGROUNDGREEN, innerBACKGROUNDBLUE)); // Set the colors of the strip
  innerStrip2.setElectronAmont(INPIXELAMOUNT); // Set the amount of electrons in the strip

  // Setup outer strip
  Serial.println("Setting up outer strip 1...");
  outerStrip.setup(BRIGHTNESS); // This initializes the strip
  outerStrip.setColors(outerStrip.Color(outerRED, outerGREEN, outerBLUE), outerStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE)); // Set the colors of the strip
  outerStrip.setElectronAmont(OUTPIXELAMOUNT); // Set the amount of electrons in the strip

  Serial.println("Setting up outer strip 2...");
  outerStrip2.setup(BRIGHTNESS);
  outerStrip2.setColors(outerStrip.Color(outerRED, outerGREEN, outerBLUE), outerStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE)); // Set the colors of the strip
  outerStrip2.setElectronAmont(OUTPIXELAMOUNT); // Set the amount of electrons in the strip

  Serial.println("Setting up outer strip 3...");
  outerStrip3.setup(BRIGHTNESS);
  outerStrip3.setColors(outerStrip.Color(outerRED, outerGREEN, outerBLUE), outerStrip.Color(outerBACKGROUNDRED, outerBACKGROUNDGREEN, outerBACKGROUNDBLUE)); // Set the colors of the strip
  outerStrip3.setElectronAmont(OUTPIXELAMOUNT); // Set the amount of electrons in the strip
  // Setup small strip
  Serial.println("Setting up small strip...");
  smallStrip.setup(BRIGHTNESS); // This initializes the strip
  smallStrip.setColors(smallStrip.Color(smallRED, smallGREEN, smallBLUE), smallStrip.Color(smallBACKGROUNDRED, smallBACKGROUNDGREEN, smallBACKGROUNDBLUE)); // Set the colors of the strip
  smallStrip.setElectronAmont(SMALLPIXELAMOUNT); // Set the amount of electrons in the strip
  Serial.println("Done setting up strips!");
}


#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266) // only include if we are on an ESP
void cloudSetup() {
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Set the colors of the strips
  innerStripColor = Color(innerRED, innerGREEN, innerBLUE);
  outerStripColor = Color(outerRED, outerGREEN, outerBLUE);
  smallStripColor = Color(smallRED, smallGREEN, smallBLUE);
  // Multi-threading setup
  Serial.print("Setup currently running on core: ");
  #ifdef ARDUINO_ARCH_ESP32
  Serial.println(xPortGetCoreID());
  delay(500);
  xTaskCreate(cloudLoop, "CloudLoop", 10000, NULL, 2, NULL);
  delay(1000);
  #elif defined(ARDUINO_ARCH_ESP8266)
  delay(500);
  // without using FreeRTOS, we can't do multi-threading, so we just run the cloud loop in the main loop, every minute or so
  Serial.println("Running cloud loop in main loop every minute");
  #endif
}
#endif

/* DONE SETUP */

void loop() {
  if (millis() - lastSwitchTime >= SWITCHTIME * 1000) { // If it has been SWITCHTIME seconds since the last switch
    runSwitch(); // Run the switch
  }
#ifdef ARDUINO_ARCH_ESP8266
  cloudLoop();
#elif defined(ARDUINO_ARCH_ESP32)
  // nothing to do here, cloud loop is running on a separate thread
#else
  blinkbuiltinled(); // Blink the builtin led to show that the program is running, but not on an ESP as the pin changes from board to board, might change in the future
#endif

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
  outerStrip3.moveColorFowardOnce();
  smallStrip.moveColorFowardOnce();
}

void updateBlinks() {
  innerStrip.updateBlink();
  innerStrip2.updateBlink();
  outerStrip.updateBlink();
  outerStrip2.updateBlink();
  outerStrip3.updateBlink();
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

#if !defined(ARDUINO_ARCH_ESP8266) && !defined(ARDUINO_ARCH_ESP32)
void blinkbuiltinled() {
  builtinLedState = !builtinLedState;
  digitalWrite(LED_BUILTIN, builtinLedState);
}
#endif

#ifdef ARDUINO_ARCH_ESP8266
void cloudLoop() {
  if (millis() - lastCloudUpdate >= 60000) { // If it has been 60 seconds since the last cloud update
    Serial.println("Updating cloud...");
    ArduinoCloud.update();
    lastCloudUpdate = millis();
  }
}
#endif

#if defined(ARDUINO_ARCH_ESP32) // only include if we are on an ESP
void cloudLoop(void *pvParameters) {
  Serial.print("Cloud Loop currently running on core: ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    ArduinoCloud.update();
  }
}
#endif


#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266) // only include if we are on an ESP
void onInnerStripColorChange() {
  Color color = innerStripColor.getValue();
  innerStrip.setElectronColor(innerStrip.ColorHSV(color.hue, color.sat, color.bri));
  innerStrip2.setElectronColor(innerStrip.ColorHSV(color.hue, color.sat, color.bri));
}

void onOuterStripColorChange() {
  Color color = outerStripColor.getValue();
  outerStrip.setElectronColor(outerStrip.ColorHSV(color.hue, color.sat, color.bri));
  outerStrip2.setElectronColor(outerStrip.ColorHSV(color.hue, color.sat, color.bri));
  outerStrip3.setElectronColor(outerStrip.ColorHSV(color.hue, color.sat, color.bri));
}

void onSmallStripColorChange() {
  Color color = smallStripColor.getValue();
  smallStrip.setElectronColor(smallStrip.ColorHSV(color.hue, color.sat, color.bri));
}

void onLedCountsChange() {
  String tmpCounts = ledCounts;
  tmpCounts.replace(" ", "");
  tmpCounts.replace(",", "");
  
  int counts[6];
  for(int i = 0; i < 6; i++) {
    counts[i] = tmpCounts.substring(i, i + 1).toInt();
  }
  
  smallStrip.setElectronAmont(counts[0]);

  innerStrip.setElectronAmont(counts[1]);
  innerStrip2.setElectronAmont(counts[2]);
  
  outerStrip.setElectronAmont(counts[3]);
  outerStrip2.setElectronAmont(counts[4]);
  outerStrip3.setElectronAmont(counts[5]);
}

void onTriggerSwitchChange() {
  runSwitch();
}
#endif
