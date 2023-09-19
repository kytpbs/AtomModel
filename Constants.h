#define UPNUMPIXELS 11 // The number of LEDs in the upper strip
#define DOWNNUMPIXELS 22 // The number of LEDs in the lower strip

#define UPDATA 13 // The pin that the upper strip is connected to
#define DOWNDATA 12 // The pin that the lower strip is connected to

#define PIXELAMOUNT 3 // The number of pixels that are lit up on each strip (will change on pixel switch)

/*
 * The number of pixels between the two pixels including the pixel that are lit up. Should be devidble by both the upper and lower number of pixels.
 * This is because we want the pixels to be evenly spaced out. IF THIS IS NOT TRUE, THE PIXELS WILL NOT BE EVENLY SPACED OUT.
*/
#define PIXELSPACE 11 


#define BRIGHTNESS 255 // The brightness of the LEDS should be a value from 0 - 255

//Electron Colors of the Lover Stshould be values from (0 - 255):
#define LOVERRED 255
#define LOVERGREEN 0
#define LOVERBLUE 255

// Electron Colors of the Upper Strip should be values from (0 - 255):
#define UPPERRED 255
#define UPPERGREEN 255
#define UPPERBLUE 0

#define DELAYTIME 75 // The amount of time between each pixel movement in milliseconds.
#define TOGETHERAMOUNT 5 // The amount of times the pixels need to be together to switch

//Blinking Constants
#define BLINKAMOUNT 3 // The amount of times the pixels blink when they switch
#define BLINKDELAY 100 // The amount of time between each blink in milliseconds
#define BLINKRED 255 // The amount of red in the blink
#define BLINKGREEN 255 // The amount of green in the blink
#define BLINKBLUE 255 // The amount of blue in the blink

//Background Color Constants
#define LOVERBACKGROUNDRED 0 // The amount of red in the background color
#define LOVERBACKGROUNDGREEN 255 // The amount of green in the background color
#define LOVERBACKGROUNDBLUE 0 // The amount of blue in the background color

#define UPPERBACKGROUNDRED 0 // The amount of red in the upper background color
#define UPPERBACKGROUNDGREEN 0 // The amount of green in the upper background color
#define UPPERBACKGROUNDBLUE 0 // The amount of blue in the upper background color
