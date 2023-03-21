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
  //read serial if test in last serial line blink green
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input == "test") {
      Serial.println("test");
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
      }
      FastLED.show();
      delay(1000);
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    }
  }
}