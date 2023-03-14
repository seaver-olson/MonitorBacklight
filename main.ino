#include <FastLED.h>//not an error Ignore please
#define NUM_LEDS 60
#define DATA_PIN 6

CRGB leds[NUM_LEDS];//create object
void setup() { 
    //specs: 3 pin 5v RGB LED strip
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);//defines ledtype and pin
}
void loop() {
    
}
void getScreenColor(){
    //get color of pixel
    //top right
    String TR = getPixelColor(0,0);
    //return color
}
//Q: How do I get the color of a pixel from the computer connected through port
 
/*
Steps:
    1. Plot out the LED strip around the Monitor Screen
    2. Create Objects that represent parts of the LED strip in correspondence to the location on the monitor
    3. Processes the Monitor Screen and determines the color of the LED strip
    4. Send the color data to the LED strip
    5. Repeat
*/