// #include <Adafruit_NeoPixel.h>
#include "FastLED.h"

// 12 * 3 faces
#define NUMPIXELS 36
#define NUMFACES 3
#define PIN A15
#define RGB 3

class LEDFaces {
  public:
    int numFaces;
    int ledsPerFace;
    // LED strip
    CRGB sensorLeds[NUMPIXELS];
    CRGB outputLeds[NUMPIXELS];
    CRGB pulseColor;

    //CRGB LEDS[NUM_LEDS_IN_STRIP];
    // unsigned long dimTimer;
    // int dimTimerInterval;
    // unsigned long pulseTimer;
    // int pulseTimerInterval;
    float pulseAngle;
    int pulseValue;
    float pulseScale;
    int pulseScales[NUMFACES];
    int hueValue;
    int saturationValue;

  LEDFaces() {
    numFaces = 3;
    ledsPerFace = 12;

    // Pulse
    pulseAngle = 0;
    hueValue = 0;
    pulseScale = 0;
    // pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

  }
  void begin() {
    // pixels.begin();
    FastLED.addLeds<NEOPIXEL, PIN>(outputLeds, NUMPIXELS);
    // Clear any LEDS to black;
    // resetLEDS();
    // show();
  }

  void updatePulseHSV(int sensor) {
    // if(millis() - pulseTimer > pulseTimerInterval) {
    //   pulseTimer = millis();
    // }
    // if(millis() - dimTimer > dimTimerInterval) {
    //   dimTimer = millis();
    // }
    // sensor = 255 - sensor;
    pulseAngle += 0.05; // speed of pulse

    // scale the sensor input
    pulseValue = abs(sin(pulseAngle)) * sensor;
    pulseScale = abs(sin(pulseAngle));
    hueValue += 1;
  }
  void updatePulseScale() {
    pulseScale = abs(sin(pulseAngle));
  }

  void fastLEDTest() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] = CHSV(255,255,255);
    }
    FastLED.show();
  }

  void sensorToLEDHSV(int face, int hSensor, int sSensor, int vSensor) {
    // Calculate position of pixels per face on the whole strip
    // ie: face 0 is 0 - 11, face 1 is 12 - 23, ...
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;

    // HSV
    int hue = hSensor;
    // int sat = 155 + map(sValue, 0, 255, 0, 100);

    //Brightness
    int pulseValue = int(pulseScale * vSensor);
    int brightness = map(hSensor, 0, 255, 0, 127) + map(pulseValue, 0, 255, 0, 127);

    for (int i = start; i < end; i++) {
      // pixels.setPixelColor(i, pixels.Color(r, g, b));
      sensorLeds[i] = CHSV(hue, 255, brightness);
      // ledsReading[i].g = g;
      // ledsReading[i].b = b;

    }
  }
  void writeSensorLEDS(int face, int r, int g, int b) {
    // Calculate position of pixels per face on the whole strip
    // ie: face 0 is 0 - 11, face 1 is 12 - 23, ...
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;

    for (int i = start; i < end; i++) {
      sensorLeds[i] = CRGB(r, g, b);

    }
  }

  void hsvPulse(int face, int sensor) {
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;
    for (int i = start; i < end; i++) {
      sensorLeds[i]= CHSV(hueValue, 255,pulseValue);
    }
  }
  void addSensorLEDS() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] += sensorLeds[i];
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
    // pulseOutputLEDS();
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
