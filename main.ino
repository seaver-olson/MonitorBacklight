#include <FastLED.h>//not an error Ignore please
#define NUM_LEDS 60
#define DATA_PIN 6

CRGB leds[NUM_LEDS];//create object
void setup() { 
    //specs: 3 pin 5v RGB LED strip
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);//defines ledtype and pin
}
void loop() {
    String screenColor = getScreenColor();
    
}
void getScreenColor(){
    //get color of pixel
    //top right
    String TR = getPixelColor(0,0);
    String TL = getPixelColor(0,sMax);
    String TM = getScreenColor(0,sMax/2);
    String BR = getPixelColor(sMax,0);
    String BL = getPixelColor(sMax,sMax);
    String BM = getScreenColor(sMax,sMax/2);
    String ML = getScreenColor(sMax/2,0);
    String MR = getScreenColor(sMax/2,sMax);
    return TR +'|'+TM+'|'+TL+'|'+ BR+'|'+ BL+'|'+BM+'|'+ML+'|'+ MR;
}
String getPixelColor(int x, int y){
    //return will be in the form of hex Ex: #FFFFFF
    //get color of pixel
    //return color
}

/*
Steps:
    1. Plot out the LED strip around the Monitor Screen
    2. Create Objects that represent parts of the LED strip in correspondence to the location on the monitor
    3. Processes the Monitor Screen and determines the color of the LED strip
    4. Send the color data to the LED strip
    5. Repeat
*/