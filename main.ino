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
void makePositive(int * ar, int size,int R, int G, int B){
        if (R < 0){
            R = R * -1;
        }
        if (G < 0){
            G = G * -1;
        }
        if (B < 0){
            B = B * -1;
        }
        if (R > 255){
            R = 255;
        }
        if (G > 255){
            G = 255;
        }
        if (B > 255){
            B = 255;
        }
      int arr[] = {R,G,B};
      for (int i=0; i< size; i++)
    {
     ar[i] = arr[i];
  }    }
//change above function so it takes in string hex instead
void makeRGB(int * ar, int size,String hex){
        //divide hex into 3 parts
        //convert each part to int
        String RB = hex.substring(0, 2);
        String GB = hex.substring(3, 5);
        String BB = hex.substring(6, 8);
        //change to ints 
        int R = (int)strtol(RB.c_str(), NULL, 16);
        int G = (int)strtol(GB.c_str(), NULL, 16);
        int B = (int)strtol(BB.c_str(), NULL, 16);
        Serial.println("R");
        Serial.println(R);
        Serial.println("G");
        Serial.println(G);
        Serial.println("B");
        Serial.println(B);
        int arr[] = {R,G,B};
        for (int i=0; i< size; i++)
        {
          ar[i] = arr[i];
      }
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
    Serial.println(top_left);
    //the above lines arent correct fix it


    //make lines above into a function
    //array of rgb tuples
    int top_leftList[2] ;
    int top_rightList[2] ;
    int bottom_leftList[2] ;
    int bottom_rightList[2] ;
    int middle_leftList[2] ;
    int middle_rightList[2] ;
    int top_middleList[2] ;
    int bottom_middleList[2] ;
    
    //make array of rgb tuples
    makeRGB(top_leftList,2,top_left);
    makeRGB(top_rightList,2,top_right);
    makeRGB(bottom_leftList,2,bottom_left);
    makeRGB(bottom_rightList,2,bottom_right);
    makeRGB(middle_leftList,2,middle_left);
    makeRGB(middle_rightList,2,middle_right);
    makeRGB(top_middleList,2,top_middle);
    makeRGB(bottom_middleList,2,bottom_middle);
    makePositive(top_leftList,2,top_leftList[0], top_leftList[1], top_leftList[2]);
    makePositive(top_rightList,2,top_rightList[0], top_rightList[1], top_rightList[2]);
    makePositive(bottom_leftList,2,bottom_leftList[0], bottom_leftList[1], bottom_leftList[2]);
    makePositive(bottom_rightList,2,bottom_rightList[0], bottom_rightList[1], bottom_rightList[2]);
    makePositive(middle_leftList,2,middle_leftList[0], middle_leftList[1], middle_leftList[2]);
    makePositive(middle_rightList,2,middle_rightList[0], middle_rightList[1], middle_rightList[2]);
    makePositive(top_middleList,2,top_middleList[0], top_middleList[1], top_middleList[2]);
    makePositive(bottom_middleList,2,bottom_middleList[0], bottom_middleList[1], bottom_middleList[2]);
    Serial.println(top_leftList[0]);
    Serial.println(top_leftList[1]);
    Serial.println(top_leftList[2]);
    CRGB Ctop_leftRGB = CRGB(top_leftList[0], top_leftList[1], top_leftList[2]);
    CRGB Ctop_rightRGB = CRGB(top_rightList[0], top_rightList[1], top_rightList[2]);
    CRGB Cbottom_leftRGB = CRGB(bottom_leftList[0], bottom_leftList[1], bottom_leftList[2]);
    CRGB Cbottom_rightRGB = CRGB(bottom_rightList[0], bottom_rightList[1], bottom_rightList[2]);
    CRGB Cmiddle_leftRGB = CRGB(middle_leftList[0], middle_leftList[1], middle_leftList[2]);
    CRGB Cmiddle_rightRGB = CRGB(middle_rightList[0], middle_rightList[1], middle_rightList[2]);
    CRGB Ctop_middleRGB = CRGB(top_middleList[0], top_middleList[1], top_middleList[2]);
    CRGB Cbottom_middleRGB = CRGB(bottom_middleList[0], bottom_middleList[1], bottom_middleList[2]);
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
