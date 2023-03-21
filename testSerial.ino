//if any text is recieved in serial port have the led strip blink green

#include <FastLED.h>

#define NUM_LEDS 128
#define DATA_PIN 8
#define LED_TYPE WS2812


CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  if (Serial.available() > 0) {
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(1000);
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(1000);
  }
}