#define OUTNUMPIXELS 160 // The number of LEDs in the outer strip
#define INNUMPIXELS 196 // The number of LEDs in the inner strip
#define SMALLNUMPIXELS 116 // The number of LEDs in the small strip

#define OUTDATA 13 // The pin that the outer strip is connected to
#define INDATA 12 // The pin that the inner strip is connected to,
#define SMALLDATA 11 // The pin that the small strip is connected to

/* NEW DEFFINITONS */
#define OUTDATA1 13 // The pin that the outer strip1 is connected to
#define OUTDATA2 12 // The pin that the outer strip2 is connected to
#define OUTDATA3 11 // The pin that the outer strip3 is connected to

#define INDATA1 10 // The pin that the inner strip1 is connected to
#define INDATA2 9 // The pin that the inner strip2 is connected to


#define INPIXELAMOUNT 8 // The number of pixels that are lit up on each strips in total (will change on pixel switch)
#define OUTPIXELAMOUNT 10 // The number of pixels that are lit up on the outside strips in total (will change on pixel switch)
#define SMALLPIXELAMOUNT 2 // The number of pixels that are lit up on the small strip (will NOT change on pixel switch)

/*
 * The number of pixels between the two pixels including the pixel that are lit up. Should be devidble by both the outer and inner number of pixels.
 * This is because we want the pixels to be evenly spaced out. IF THIS IS NOT TRUE, THE PIXELS WILL NOT BE EVENLY SPACED OUT.
*/
#define DEFAULTPIXELSPACE 12
#define INPIXELSPACE INNUMPIXELS/INPIXELAMOUNT
#define OUTPIXELSPACE OUTNUMPIXELS/OUTPIXELAMOUNT
#define SMALLPIXELSPACE SMALLNUMPIXELS/SMALLPIXELAMOUNT


#define BRIGHTNESS 255 // The brightness of the LEDS should be a value from 0 - 255

//Electron Colors of the small Strip should be values from (0 - 255):
#define smallRED 255
#define smallGREEN 0
#define smallBLUE 180

//Electron Colors of the inner Stshould be values from (0 - 255):
#define innerRED 255
#define innerGREEN 0
#define innerBLUE 255

// Electron Colors of the outer Strip should be values from (0 - 255):
#define outerRED 0
#define outerGREEN 0
#define outerBLUE 255

#define DELAYTIME 0 // The amount of time between each pixel movement in milliseconds.
#define TOGETHERAMOUNT 2 // The amount of times the pixels need to be together to switch

//Blinking Constants
#define BLINKAMOUNT 3 // The amount of times the pixels blink when they switch
#define BLINKDELAY 100 // The amount of time between each blink in milliseconds
#define BLINKRED 255 // The amount of red in the blink
#define BLINKGREEN 255 // The amount of green in the blink
#define BLINKBLUE 255 // The amount of blue in the blink

//Background Color Constants
#define smallBACKGROUNDRED 0 // The amount of red in the background color
#define smallBACKGROUNDGREEN 2 // The amount of green in the background color
#define smallBACKGROUNDBLUE 10 // The amount of blue in the background color

#define innerBACKGROUNDRED 8 // The amount of red in the background color
#define innerBACKGROUNDGREEN 0 // The amount of green in the background color
#define innerBACKGROUNDBLUE 2 // The amount of blue in the background color

#define outerBACKGROUNDRED 400/100 // The amount of red in the outer background color
#define outerBACKGROUNDGREEN 165/100 // The amount of green in the outer background color
#define outerBACKGROUNDBLUE 0 // The amount of blue in the outer background color
