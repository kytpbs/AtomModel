#define UPNUMPIXELS 11 // The number of LEDs in the upper strip
#define DOWNNUMPIXELS 22 // The number of LEDs in the lower strip

#define UPDATA 13 // The pin that the upper strip is connected to
#define DOWNDATA 12 // The pin that the lower strip is connected to

#define PIXELAMOUNT 3 // The number of pixels that are lit up on each strip (will change on pixel switch)
#define PIXELSPACE 11 // The number of pixels between the two pixels that are lit up

#define BRIGHTNESS 50 // Should be a value from 0 - 255
//Electron Colors should be values from (0 - 255):
#define RED 0
#define GREEN 255
#define BLUE 255

#define DELAYTIME 75 // The amount of time between each pixel movement in milliseconds.
#define TOGETHERAMOUNT 5 // The amount of times the pixels need to be together to switch

//Blinking Constants
#define BLINKAMOUNT 3 // The amount of times the pixels blink when they switch
#define BLINKDELAY 100 // The amount of time between each blink in milliseconds
#define BLINKRED 255 // The amount of red in the blink
#define BLINKGREEN 255 // The amount of green in the blink
#define BLINKBLUE 255 // The amount of blue in the blink
