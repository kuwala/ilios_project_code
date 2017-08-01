// #include <Adafruit_NeoPixel.h>
#include "FastLED.h"

// 12 * 3 faces
#define NUMPIXELS 36
#define PIN A15
#define RGB 3

class LEDFaces {
  public:
    int numFaces;
    int ledsPerFace;

    // 2d array for holding RGB values of each LED
    // needs to be optimized to smaller variable times other then ints
    //int leds[RGB][NUMPIXELS];

    // Adafruit_NeoPixel pixels;
    CRGB sensorLeds[NUMPIXELS];
    CRGB outputLeds[NUMPIXELS];
    CRGB pulseColor;
    CRGB pulseValue;
    //CRGB LEDS[NUM_LEDS_IN_STRIP];
    unsigned long dimTimer;
    int dimTimerInterval;
    unsigned long pulseTimer;
    int pulseTimerInterval;

  LEDFaces() {
    numFaces = 3;
    ledsPerFace = 12;
    pulseTimer = 0;
    pulseTimerInterval = 500;
    dimTimer = 0;
    dimTimerInterval = 10;
    pulseColor = CRGB(127,0,0);
    // pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

  }
  void begin() {
    // pixels.begin();
    FastLED.addLeds<NEOPIXEL, PIN>(outputLeds, NUMPIXELS);
    // Clear any LEDS to black;
    // resetLEDS();
    // show();
  }

  void updatePulse() {
    // Trigger pulse
    if(millis() - pulseTimer > pulseTimerInterval) {
      pulseValue = CRGB(32, 0, 16);
      pulseTimer = millis();
    }
    // Dim pulse
    if(millis() - dimTimer > dimTimerInterval) {
      pulseValue.fadeToBlackBy(10);
      dimTimer = millis();
    }

      // pulseValue.fadeToBlackBy(1);
    // if(pulseValue > 0) {
    // } else {
    //   pulseValue = 0;
    // }

    // makes the leds pulse
  }

  void fastLEDTest() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] = CRGB::Blue;
    }
    FastLED.show();
  }
  void writeSensorLEDS(int face, int r, int g, int b) {
    // Calculate position of pixels per face on the whole strip
    // ie: face 0 is 0 - 11, face 1 is 12 - 23, ...
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;

    for (int i = start; i < end; i++) {
      // pixels.setPixelColor(i, pixels.Color(r, g, b));
      sensorLeds[i] = CRGB(r, g, b);
      // ledsReading[i].g = g;
      // ledsReading[i].b = b;

    }
  }
  void addSensorLEDS() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] += sensorLeds[i];
      // outputLeds[i] += CRGB::Red;
    }
  }
  void addPulseLEDS() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] +=  pulseValue;
    }
  }
  void resetLEDSOUT() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] = CRGB::Black;
    }
  }
  void show() {
    // Clear the strip
    resetLEDSOUT();
    // Add rgb values from sensors to strip
    addSensorLEDS();
    // add pulse RGB values to strip
    addPulseLEDS();
    // pulse
    FastLED.show();
  }
  // void resetLEDS() {
  //   for (size_t i = 0; i < numFaces; i++) {
  //     drawLEDS(i, 0,0,0);
  //   }
  // }

};
