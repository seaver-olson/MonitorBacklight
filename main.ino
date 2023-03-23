/*
Seaver Olson
Project: LED Strip Monitor 
Date: 3/15/2023
*/
#include <FastLED.h>//not an error Ignore please
#define NUM_LEDS 120
#define DATA_PIN 8
String top_left;
String top_right;
String bottom_left;
String bottom_right;
String middle_left;
String middle_right;
String top_middle;
String bottom_middle;

int part_num = NUM_LEDS / 8;
//create objects that represent the parts of the LED strip
//top left
int[][] ledObjects = new int[7][part_num];
for (int i = 0; i < 7; i++){
    for (int j = 0; j < part_num; j++){
        ledObjects[i][j] = j + (i * part_num);
    }
}
CRGB leds[NUM_LEDS];//create object
void setup() { 
    //specs: 3 pin 5v RGB LED strip
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);//defines ledtype and pin
    //divide strip into 8 parts
    


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
    //print the colors to the serial monitor
    Serial.println(top_left);
    Serial.println(top_right);
    Serial.println(bottom_left);
    Serial.println(bottom_right);
    Serial.println(middle_left);
    Serial.println(middle_right);
    Serial.println(top_middle);
    Serial.println(bottom_middle);
    /*
    top_left = part_num[0];
    top_right = part_num[1];
    bottom_left = part_num[2];
    bottom_right = part_num[3];
    middle_left = part_num[4];
    middle_right = part_num[5];
    top_middle = part_num[6];
    bottom_middle = part_num[7];
    */
    //set the color of part_num to the color of the screen
    for (int i = 0; i < part_num; i++){
        //set to hex of top_left
        leds[ledObjects[0][i]] = strtol(top_left, NULL, 0);
        leds[ledObjects[1][i]] = strtol(top_right, NULL, 0);
        leds[ledObjects[2][i]] = strtol(bottom_left, NULL, 0);
        leds[ledObjects[3][i]] = strtol(bottom_right, NULL, 0);
        leds[ledObjects[4][i]] = strtol(middle_left, NULL, 0);
        leds[ledObjects[5][i]] = strtol(middle_right, NULL, 0);
        leds[ledObjects[6][i]] = strtol(top_middle, NULL, 0);
        leds[ledObjects[7][i]] = strtol(bottom_middle, NULL, 0);
    }
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
