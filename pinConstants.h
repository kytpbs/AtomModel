#define UPNUMPIXELS 15 // The number of LEDs in the upper strip
#define DOWNNUMPIXELS 15 // The number of LEDs in the lower strip

// The Pins of the data pins of the LED strips
int upperLedPins[] = {13};
#define lengthUpper sizeof(upperLedPins) / sizeof(upperLedPins[0])
int lowerLedPins[] = {12};
#define lengthLower sizeof(lowerLedPins) / sizeof(lowerLedPins[0])