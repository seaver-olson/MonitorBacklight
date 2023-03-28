#include <FastLED.h>//not an error Ignore please
#define NUM_LEDS 120
#define DATA_PIN 8
#define part_num NUM_LEDS / 8
CRGB leds[NUM_LEDS];//create object
void setup() { 
    //specs: 3 pin 5v RGB LED strip
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);//defines ledtype and pin
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
void formatRGB(int * ar, int size, String color){
    ar[0] = color.substring(0, 3).toInt();
    ar[1] = color.substring(3, 6).toInt();
    ar[2] = color.substring(6, 9).toInt();
}
void loop(){
    if (getScreenColor() != ""){
        int color = getScreenColor();
        top_left = color.substring(0, 9);
        top_right = color.substring(9, 18);
        bottom_left = color.substring(18, 27);
        bottom_right = color.substring(27, 36);
        middle_left = color.substring(36, 45);
        middle_right = color.substring(45, 54);
        top_middle = color.substring(54, 63);
        bottom_middle = color.substring(63, 72);
        int top_left_ar[2];
        formatRGB(top_left_ar, 3, top_left);
        int top_right_ar[2];
        formatRGB(top_right_ar, 3, top_right);
        int bottom_left_ar[2];
        formatRGB(bottom_left_ar, 3, bottom_left);
        int bottom_right_ar[2];
        formatRGB(bottom_right_ar, 3, bottom_right);
        int middle_left_ar[2];
        formatRGB(middle_left_ar, 3, middle_left);
        int middle_right_ar[2];
        formatRGB(middle_right_ar, 3, middle_right);
        int top_middle_ar[2];
        formatRGB(top_middle_ar, 3, top_middle);
        int bottom_middle_ar[2];
        formatRGB(bottom_middle_ar, 3, bottom_middle);
    for (int i = 0; i < part_num; i++){
        leds[i] = (top_left_ar[0], top_left_ar[1], top_left_ar[2]);
        leds[i+part_num] = (top_right_ar[0], top_right_ar[1], top_right_ar[2]);
        leds[i+part_num*2] = (bottom_left_ar[0], bottom_left_ar[1], bottom_left_ar[2]);
        leds[i+part_num*3] = (bottom_right_ar[0], bottom_right_ar[1], bottom_right_ar[2]);
        leds[i+part_num*4] = (middle_left_ar[0], middle_left_ar[1], middle_left_ar[2]); 
        leds[i+part_num*5] = (middle_right_ar[0], middle_right_ar[1], middle_right_ar[2]);  
        leds[i+part_num*6] = (top_middle_ar[0], top_middle_ar[1], top_middle_ar[2]);        
        leds[i+part_num*7] = (bottom_middle_ar[0], bottom_middle_ar[1], bottom_middle_ar[2]);      
    }
}