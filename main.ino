/*
Seaver Olson
Project: LED Strip Monitor 
Date: 3/15/2023
*/
#include <FastLED.h>//not an error Ignore please
#define NUM_LEDS 60
#define DATA_PIN 6

CRGB leds[NUM_LEDS];//create object
void setup() { 
    //specs: 3 pin 5v RGB LED strip
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);//defines ledtype and pin
    //set all leds to white on start up after pause for 2 seconds
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::White;
        FastLED.show();
        delay(50);
    }
}
void loop() {
    String screenColor = getScreenColor();
    top_left, top_right, bottom_left, bottom_right, middle_left, middle_right, top_middle, bottom_middle = screenColor.split("|");

}
void getScreenColor(){
    //ordinator.py will return a string of the color of the screen
    //listen for the string once a line is recieved stop listening and take the most recent line
    //return the string
    if (Serial.available() > 0) {
        String color = Serial.readStringUntil('\n');
        return color;
    }
}
void patternRandom(){
    //when the user doesn't want adaptive lighting choose from random other designs

}
void patternRainbow(){
    //FastLED rainbow pattern
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(i, 255, 255);
        }
    FastLED.show();
    delay(1000 / 60);//60 fps
}
void patternSolid(){
    //solid color
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
        }
    FastLED.show();
    delay(1000 / 60);//60 fps
}
/*
Steps:
    1. Plot out the LED strip around the Monitor Screen
    2. Create Objects that represent parts of the LED strip in correspondence to the location on the monitor
    3. Processes the Monitor Screen and determines the color of the LED strip
    4. Send the color data to the LED strip
    5. Repeat
*/
