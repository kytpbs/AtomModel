#define OUTNUMPIXELS 11 // The number of LEDs in the outer strip
#define INNUMPIXELS 22 // The number of LEDs in the inner strip

#define OUTDATA 13 // The pin that the outer strip is connected to
#define INDATA 12 // The pin that the inner strip is connected to

#define PIXELAMOUNT 3 // The number of pixels that are lit up on each strip (will change on pixel switch)

/*
 * The number of pixels between the two pixels including the pixel that are lit up. Should be devidble by both the outer and inner number of pixels.
 * This is because we want the pixels to be evenly spaced out. IF THIS IS NOT TRUE, THE PIXELS WILL NOT BE EVENLY SPACED OUT.
*/
#define PIXELSPACE 11 


#define BRIGHTNESS 255 // The brightness of the LEDS should be a value from 0 - 255

//Electron Colors of the inner Stshould be values from (0 - 255):
#define innerRED 255
#define innerGREEN 0
#define innerBLUE 255

// Electron Colors of the outer Strip should be values from (0 - 255):
#define outerRED 255
#define outerGREEN 255
#define outerBLUE 0

#define DELAYTIME 75 // The amount of time between each pixel movement in milliseconds.
#define TOGETHERAMOUNT 5 // The amount of times the pixels need to be together to switch

//Blinking Constants
#define BLINKAMOUNT 3 // The amount of times the pixels blink when they switch
#define BLINKDELAY 100 // The amount of time between each blink in milliseconds
#define BLINKRED 255 // The amount of red in the blink
#define BLINKGREEN 255 // The amount of green in the blink
#define BLINKBLUE 255 // The amount of blue in the blink

//Background Color Constants
#define innerBACKGROUNDRED 0 // The amount of red in the background color
#define innerBACKGROUNDGREEN 255 // The amount of green in the background color
#define innerBACKGROUNDBLUE 0 // The amount of blue in the background color

#define outerBACKGROUNDRED 0 // The amount of red in the outer background color
#define outerBACKGROUNDGREEN 0 // The amount of green in the outer background color
#define outerBACKGROUNDBLUE 0 // The amount of blue in the outer background color
