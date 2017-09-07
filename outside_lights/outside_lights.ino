/*
  This is a led strip around the perimeter of the dome
  the strip has a colorwheel on it that rools the colors

*/
#include "FastLED.h"
#define PIN 6
#define NUMLEDS 720

#define MINBRIGHTNESS 32
#define MAXBRIGHTNESS 127

int stepTime = 50;
int rootHue = 0;
int baseBrightness = 32;
int brightness = 88;
float brightnessAngle = 0;


CRGB leds[NUMLEDS];
int hue = 0;
void setup() {
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUMLEDS);
  Serial.begin(230400);
  //fill strip with hsv rgb lights

for (size_t i = 0; i < 21; i++) {
    float change = linearTween(i * 50.0, 220, 1000.0, 0.0);
    Serial.println(change);
  }
}

void drawLeds() {
  for (size_t i = 0; i < NUMLEDS; i++) {
    hue = (rootHue + i ) % 255;
    // leds[i] = CHSV(rootHue + hue, 127, (rootHue + i)% brightness);
    leds[i] = CHSV(rootHue + hue, 180, baseBrightness + brightness * abs(sin(brightnessAngle)));
   }
}

float linearTween(float currentTime, float changeInValue, float duration, float startValue) {
  return ( changeInValue * currentTime / duration ) + startValue;
}
void loop() {

  // Change the 3 and 0.03 here to incrase the rotate
  // of the glow
  rootHue = ( rootHue + 3 ) % 255;
  brightnessAngle += 0.03;
  drawLeds();
  FastLED.show();
  // delay(stepTime);
  delay(1);
  // a hsv colorwheel that
  // rolls the led lights around the perimeter
  // gets intense over 10 seconds faster color rool speed
  // gets brighter

}
