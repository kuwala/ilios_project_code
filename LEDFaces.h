#include "FastLED.h"

// 12 * 3 faces
#define NUMPIXELS 36
#define PIN A15
#define RGB 3

class LEDFaces {
  public:
    int numFaces;
    int ledsPerFace;
    // LED strip pixel containers
    CRGB sensorLeds[NUMPIXELS];
    CRGB outputLeds[NUMPIXELS];
    CRGB pulseColor;

    float pulseAngle;
    float pulseScale;
    int pulseValue;
    int saturationValue;
    int face0Brightness;

  LEDFaces() {
    numFaces = 3;
    ledsPerFace = 12;
    pulseColor = CRGB(127,0,0);
    pulseAngle = 0;
    pulseValue = 0;
    face0Brightness = 0;
  }

  void begin() {
    FastLED.addLeds<NEOPIXEL, PIN>(outputLeds, NUMPIXELS);
  }

  void updatePulseHSV() {
    // if(millis() - pulseTimer > pulseTimerInterval) {
    //   pulseTimer = millis();
    // }
    // if(millis() - dimTimer > dimTimerInterval) {
    //   dimTimer = millis();
    // }
    // sensor = 255 - sensor;

    pulseAngle += 0.04; // speed of pulse

    // scale the sensor input
    // pulseValue = abs(sin(pulseAngle)) * sensor;
    pulseScale = abs(sin(pulseAngle));
  }

  float getPulseScale() {
    return pulseScale;
  }
  float getFaceBrightness(int face) {
    return face0Brightness;
  }

  void fastLEDTest() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] = CHSV(255,255,255);
    }
    FastLED.show();
  }

  void pulseFace(int face, int hueVal, int satVal, int brightVal, int pulseValue) {
    // Calculate position of pixels per face on the whole strip
    // ie: face 0 is 0 - 11, face 1 is 12 - 23 ...
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;

    // Use HSV values to set the color and pulse the face
    int hue = hueVal;
    int sat = satVal;
    int scaledPulseValue = pulseValue * pulseScale;
    // Serial.println("ScaledPulse: " +  scaledPulseValue);


    // total value (brightness) is the addition of the pulse and the brightness
    int val = map(brightVal, 0, 255, 0, 127) + map(scaledPulseValue, 0, 255, 0, 127);
    face0Brightness = val;

    for (int i = start; i < end; i++) {
      sensorLeds[i] = CHSV(hue, sat, val);

    }
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

  void hsvPulse(int face, int sensor) {
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;
    for (int i = start; i < end; i++) {
      // sensorLeds[i]= CHSV(hueValue, 255,pulseValue);
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
