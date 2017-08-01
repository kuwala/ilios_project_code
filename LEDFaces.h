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
    float pulseScaler;
    float pulseScalerMax;
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
    dimTimerInterval = 2;
    pulseColor = CRGB(127,0,0);
    pulseScaler = 0.1;
    pulseScalerMax = 1.5;
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
      pulseValue = CRGB(10, 0, 4);
      pulseTimer = millis();
      pulseScaler = pulseScalerMax;
    }
    // Dim pulse
    if(millis() - dimTimer > dimTimerInterval) {
      Serial.println("OUT R");
      outputLeds[0].r = outputLeds[0].r * pulseScaler;
      Serial.println(outputLeds[0].r);
      Serial.println(" END R ");
      pulseValue.fadeToBlackBy(10);

      // dim the pulse scaler
      if (pulseScaler > 0.5) {
        pulseScaler -= 0.01;
        Serial.println("pulse Scaler");
        Serial.println(pulseScaler);
      }
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
  void pulseOutputLEDS() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      // sensorLeds[i] *= pulseScaler;
      outputLeds[i].r = outputLeds[0].r * pulseScaler;
      outputLeds[i].g = outputLeds[i].g * pulseScaler;
      outputLeds[i].b = outputLeds[i].b * pulseScaler;
    }
  }
  void addSensorLEDS() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] += sensorLeds[i];
      // outputLeds[i].r += sensorLeds[i].r;
      // outputLeds[i].g += sensorLeds[i].g;
      // outputLeds[i].b += sensorLeds[i].b;
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
    pulseOutputLEDS();
    addSensorLEDS();
    // add pulse RGB values to strip
    // addPulseLEDS();
    // pulse
    FastLED.show();
  }
  // void resetLEDS() {
  //   for (size_t i = 0; i < numFaces; i++) {
  //     drawLEDS(i, 0,0,0);
  //   }
  // }

};
