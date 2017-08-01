#include <Adafruit_NeoPixel.h>

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

    Adafruit_NeoPixel pixels;
    //CRGB LEDS[NUM_LEDS_IN_STRIP];
    unsigned long timer;
    int timeInterval;

  LEDFaces() {
    numFaces = 3;
    ledsPerFace = 12;
    pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

  }
  void begin() {
    pixels.begin();
    // Clear any LEDS to black;
    resetLEDS();
    show();
  }

  void update() {
    if(millis() - timer > timeInterval) {

    }

  }
  void drawLEDS(int face, int r, int g, int b) {
    // Calculate position of pixels per face on the whole strip
    // ie: face 0 is 0 - 11, face 1 is 12 - 23, ...
    int start = ledsPerFace * face;
    int end = start + ledsPerFace;

    for (int i = start; i < end; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));

    }
  }
  void show() {
    pixels.show();
  }
  void resetLEDS() {
    for (size_t i = 0; i < numFaces; i++) {
      drawLEDS(i, 0,0,0);
    }
  }

};
