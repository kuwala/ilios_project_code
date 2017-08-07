#include "FastLED.h"

// 12 * 3 faces
#define NUMPIXELS 72
#define LEDS_PER_FACE 12
#define PIN A15
#define NUMFACES 6
#define HUE_POINTS_PER_FACE 2

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
    int hueOffset[3];
    int hueRanges[NUMFACES][HUE_POINTS_PER_FACE];

    unsigned long hueOffsetTimer;
    int hueOffsetTimerInterval;

  LEDFaces() {
    numFaces = NUMFACES;
    ledsPerFace = LEDS_PER_FACE;
    pulseColor = CRGB(127,0,0);
    pulseAngle = 0;
    pulseValue = 0;
    face0Brightness = 0;
    hueOffsetTimer = 0;
    hueOffsetTimerInterval = 50;

    // init hue rotation Array
    for (size_t i = 0; i < NUMFACES; i++) {
      hueOffset[i] = 0;
    }
    // int hueRanges Array
    for (size_t i = 0; i < NUMFACES; i++) {
      for (size_t j = 0; j < HUE_POINTS_PER_FACE; j++) {
        hueRanges[i][j] = 127;
      }
    }
    // hueRanges[0][0] = 0;
    // hueRanges[0][1] = 200;
  }

  void begin() {
    FastLED.addLeds<NEOPIXEL, PIN>(outputLeds, NUMPIXELS);
  }

  void rotateHueOffset(int face) {
    if(millis() - hueOffsetTimer > hueOffsetTimerInterval) {
      hueOffsetTimer = millis();
      hueOffset[face] += 1;
    }
  }
  void setHueRanges(int face, int color1, int color2) {
    // color1 and color2 for the first sensor
    hueRanges[face][0] = color1;
    hueRanges[face][1] = color2;


  }

  void updatePulse() {
    // Updates the pulseBrightness modifer variables

    // if(millis() - pulseTimer > pulseTimerInterval) {
    //   pulseTimer = millis();
    // }
    // if(millis() - dimTimer > dimTimerInterval) {
    //   dimTimer = millis();
    // }
    // sensor = 255 - sensor;

    pulseAngle += 0.08; // speed of pulse

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

  void setFaceHue(int face, int hueVal) {
    hueOffset[face] = hueVal;
  }
  void pulseFace(int face, int hueVal, int satVal, int brightVal, int pulseValue) {
    // Calculate position of pixels per face on the whole strip
    // ie: face 0 is 0 - 11, face 1 is 12 - 23 ...
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;

    // Use HSV values to set the color and pulse the face
    // int hue = (hueVal + hueOffset[face]) % 256;
    // int hue = hueOffset[face] + map(hueVal, 0, 255, 0, 64);

    // map hueVal to the hueRanges
    int hue = map(hueVal, 0, 255, hueRanges[face][0], hueRanges[face][1]);
    // Serial.println("hue:" + String(hue));
    // Serial.println("1:" + String(hueRanges[face][0]));
    // Serial.println("2:" + String(hueRanges[face][1]));

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
  void fadeInFace(int face, int r, int g, int b) {
    // Calculate position of pixels per face on the whole strip
    // ie: face 0 is 0 - 11, face 1 is 12 - 23, ...
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;

    // use rgb values to fade in the face
    for (int i = start; i < end; i++) {
      sensorLeds[i] = CRGB(r, g, b);
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
  void resetLEDSOUT() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] = CRGB::Black;
    }
  }
void fastLEDTest() {
    for (size_t i = 0; i < NUMPIXELS; i++) {
      outputLeds[i] = CHSV(255,127,255);
      // outputLeds[i] = CRGB(255,255,255);
    }
    FastLED.show();
  }
void show() {
    // Clear the strip
    resetLEDSOUT();
    // Add rgb values from sensors to strip
    addSensorLEDS();
    // add pulse RGB values to strip
    // addPulseLEDS();
    // pulse
    FastLED.show();
  }

};
