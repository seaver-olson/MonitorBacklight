/*
Seaver Olson
Project: LED Strip Monitor 
Date: 3/15/2023
*/
#include <FastLED.h>//not an error Ignore please
#define NUM_LEDS 120
#define DATA_PIN 8

String top_left, top_right, bottom_left, bottom_right, middle_left, middle_right, top_middle, bottom_middle;
const int part_num = NUM_LEDS / 8;

CRGB leds[NUM_LEDS];//create object
void setup() { 
    //specs: 3 pin 5v RGB LED strip
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);//defines ledtype and pin
}
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
String getScreenColor(){
    //ordinator.py will return a string of the color of the screen
    //listen for the string once a line is recieved stop listening and take the most recent line
    //return the string
    if (Serial.available() > 0) {
        String color = Serial.readStringUntil('\n');
        return color;
    }
    else{
      return "";
    }
}
void rainbow() {
    // FastLED's built-in rainbow generator
    fill_rainbow( leds, NUM_LEDS, gHue, 7);
}
void rainbowWithGlitter() {
    // built-in FastLED rainbow, plus some random sparkly glitter
    rainbow();
    addGlitter(80);
}
void addGlitter( fract8 chanceOfGlitter) {
    if( random8() < chanceOfGlitter) {
        leds[ random16(NUM_LEDS) ] += CRGB::White;
    }
}
void confetti() {
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy( leds, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV( gHue + random8(64), 200, 255);
}
void sinelon() {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy( leds, NUM_LEDS, 20);
    int pos = beatsin16( 13, 0, NUM_LEDS-1 );
    leds[pos] += CHSV( gHue, 255, 192);
}
void bpm() {
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    for( int i = 0; i < NUM_LEDS; i++) { //9948
        leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    }
}
void juggle() {
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy( leds, NUM_LEDS, 20);
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
        leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}
void changePattern(){
    //change pattern
    gCurrentPatternNumber = (gCurrentPatternNumber + 1) % 6;
    gHue = 0;
}


void patternSolid(){
    //solid color
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
        }
    FastLED.show();
    delay(1000 / 60);//60 fps
}
void loop() {
    String screenColor = getScreenColor();
    //if serial is not empty print last line of serial
    //split string into 8 parts
    if (screenColor != ""){
    top_left = screenColor.substring(0, 6);
    top_right = screenColor.substring(7, 13);
    bottom_left = screenColor.substring(14, 20);
    bottom_right = screenColor.substring(21, 27);
    middle_left = screenColor.substring(28, 34);
    middle_right = screenColor.substring(35, 41);
    top_middle = screenColor.substring(42, 48);
    bottom_middle = screenColor.substring(49, 55);

    //convert all hex nums to rgb tuples
    int top_leftRGB = (long) strtol( &top_left[1], NULL, 16);
    int top_rightRGB = (long) strtol( &top_right[1], NULL, 16);
    int bottom_leftRGB = (long) strtol( &bottom_left[1], NULL, 16);
    int bottom_rightRGB = (long) strtol( &bottom_right[1], NULL, 16);
    int middle_leftRGB = (long) strtol( &middle_left[1], NULL, 16);
    int middle_rightRGB = (long) strtol( &middle_right[1], NULL, 16);
    int top_middleRGB = (long) strtol( &top_middle[1], NULL, 16);
    int bottom_middleRGB = (long) strtol( &bottom_middle[1], NULL, 16);
    //the above lines arent correct fix it
    Serial.println(top_leftRGB);

    //make lines above into a function
    int[] makeRGB(int hex){
        int R = (hex >> 16);
        int G = (hex >> 8 & 0xFF);
        int B = (hex & 0xFF);
        return [R, G, B];
    }
    top_leftR, top_leftG, top_leftB = makeRGB(top_leftRGB);
    top_rightR, top_rightG, top_rightB = makeRGB(top_rightRGB);
    bottom_leftR, bottom_leftG, bottom_leftB = makeRGB(bottom_leftRGB);
    bottom_rightR, bottom_rightG, bottom_rightB = makeRGB(bottom_rightRGB);
    middle_leftR, middle_leftG, middle_leftB = makeRGB(middle_leftRGB);
    middle_rightR, middle_rightG, middle_rightB = makeRGB(middle_rightRGB);
    top_middleR, top_middleG, top_middleB = makeRGB(top_middleRGB);
    bottom_middleR, bottom_middleG, bottom_middleB = makeRGB(bottom_middleRGB);

    int[] makePositive(int R, int G, int B){
        if (R < 0){
            R = R * -1;
        }
        if (G < 0){
            G = G * -1;
        }
        if (B < 0){
            B = B * -1;
        }
        return [R, G, B];
    }
    top_leftR, top_leftG, top_leftB = makePositive(top_leftR, top_leftG, top_leftB);
    top_rightR, top_rightG, top_rightB = makePositive(top_rightR, top_rightG, top_rightB);
    bottom_leftR, bottom_leftG, bottom_leftB = makePositive(bottom_leftR, bottom_leftG, bottom_leftB);
    bottom_rightR, bottom_rightG, bottom_rightB = makePositive(bottom_rightR, bottom_rightG, bottom_rightB);
    middle_leftR, middle_leftG, middle_leftB = makePositive(middle_leftR, middle_leftG, middle_leftB);
    middle_rightR, middle_rightG, middle_rightB = makePositive(middle_rightR, middle_rightG, middle_rightB);
    top_middleR, top_middleG, top_middleB = makePositive(top_middleR, top_middleG, top_middleB);
    bottom_middleR, bottom_middleG, bottom_middleB = makePositive(bottom_middleR, bottom_middleG, bottom_middleB);
    //make tuples
    CRGB Ctop_leftRGB = CRGB(top_leftR, top_leftG, top_leftB);
    CRGB Ctop_rightRGB = CRGB(top_rightR, top_rightG, top_rightB);
    CRGB Cbottom_leftRGB = CRGB(bottom_leftR, bottom_leftG, bottom_leftB);
    CRGB Cbottom_rightRGB = CRGB(bottom_rightR, bottom_rightG, bottom_rightB);
    CRGB Cmiddle_leftRGB = CRGB(middle_leftR, middle_leftG, middle_leftB);
    CRGB Cmiddle_rightRGB = CRGB(middle_rightR, middle_rightG, middle_rightB);
    CRGB Ctop_middleRGB = CRGB(top_middleR, top_middleG, top_middleB);
    CRGB Cbottom_middleRGB = CRGB(bottom_middleR, bottom_middleG, bottom_middleB);

    //CRGB Ctop_leftRGB = CRGB(makePositive(makeRGB(top_leftRGB))); possibly try this later

    for (int i = 0; i < part_num; i++){
        //set to hex of top_left
        
        //leds 0-15 = top_left
        leds[i] = Ctop_leftRGB;
        leds[i+part_num] = Ctop_rightRGB;
        leds[i+part_num*2] = Cbottom_leftRGB;
        leds[i+part_num*3] = Cbottom_rightRGB;
        leds[i+part_num*4] = Cmiddle_leftRGB;
        leds[i+part_num*5] = Cmiddle_rightRGB;
        leds[i+part_num*6] = Ctop_middleRGB;
        leds[i+part_num*7] = Cbottom_middleRGB;
        
        
        //add8e6|add8e6|add8e6|add8e6|add8e6|add8e6|add8e6|add8e6
    }
    //set all brightness to 255
    FastLED.setBrightness(255);
    FastLED.show();
    delay(500);
    }
}
/*
Steps:
    1. Plot out the LED strip around the Monitor Screen
    2. Create Objects that represent parts of the LED strip in correspondence to the location on the monitor
    3. Processes the Monitor Screen and determines the color of the LED strip
    4. Send the color data to the LED strip
    5. Repeat
*/
