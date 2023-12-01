#include "stripCommands.h"

unsigned long lastSwitchTime = 0; // Create a variable to store the last switch time

namespace stripCommands {
    void runSwitch() {
        Serial.println("Blinking! as " + String(SWITCHTIME) + " Seconds have passed."); // Print that we are blinking
        lastSwitchTime = millis(); // Set the last switch time to the current time
        blinkAll(BLINKAMOUNT); // Blink the pixels
        switchPixel(); // Switch the pixels
        return;
    }

    void moveElectronFoward() {
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

    bool shouldSwitch() {
        return millis() - lastSwitchTime >= SWITCHTIME * 1000;
    }
}