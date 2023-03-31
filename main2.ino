#include <FastLED.h>//not an error Ignore please
#define NUM_LEDS 128
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
    String color = getScreenColor();
    if (color != ""){
        String top_left = color.substring(0, 9);
        String top_right = color.substring(9, 18);
        String bottom_left = color.substring(18, 27);
        String bottom_right = color.substring(27, 36);
        String middle_left = color.substring(36, 45);
        String middle_right = color.substring(45, 54);
        String top_middle = color.substring(54, 63);
        String bottom_middle = color.substring(63, 72);
        //007176211019177211015171206015171205004168204012171205011175210021166199
        int top_left_ar[2];
        formatRGB(top_left_ar, 3, top_left);
        Serial.println(top_left_ar[0]);
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
        Serial.println(top_left_ar[0]);
        leds[i].r = top_left_ar[0];
        leds[i].g = top_left_ar[1];
        leds[i].b = top_left_ar[2];
        leds[i + part_num].r = top_right_ar[0];
        leds[i + part_num].g = top_right_ar[1];
        leds[i + part_num].b = top_right_ar[2];
        leds[i + part_num * 2].r = bottom_left_ar[0];
        leds[i + part_num * 2].g = bottom_left_ar[1];
        leds[i + part_num * 2].b = bottom_left_ar[2];
        leds[i + part_num * 3].r = bottom_right_ar[0];
        leds[i + part_num * 3].g = bottom_right_ar[1];
        leds[i + part_num * 3].b = bottom_right_ar[2];
        leds[i + part_num * 4].r = middle_left_ar[0];
        leds[i + part_num * 4].g = middle_left_ar[1];
        leds[i + part_num * 4].b = middle_left_ar[2];
        leds[i + part_num * 5].r = middle_right_ar[0];
        leds[i + part_num * 5].g = middle_right_ar[1];
        leds[i + part_num * 5].b = middle_right_ar[2];
        leds[i + part_num * 6].r = top_middle_ar[0];
        leds[i + part_num * 6].g = top_middle_ar[1];
        leds[i + part_num * 6].b = top_middle_ar[2];
        leds[i + part_num * 7].r = bottom_middle_ar[0];
        leds[i + part_num * 7].g = bottom_middle_ar[1];
        leds[i + part_num * 7].b = bottom_middle_ar[2]; 
        FastLED.setBrightness(100);
      FastLED.show();
      delay(500);  
    }
}}