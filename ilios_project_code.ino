/*
    ilios project led controller
    by Jonathon Mooney
    code by Jonathon Mooney, Daniel Smolentsev

    code description:
    the led controller receives serial data (from a max patch) in a string format [ r g b r2 g2 b2 r3 g3 b3 ... ]
    each set of rgb values is then pushed to the neopixel rings on each side.


*/

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#include "ilios_proximity_controller.h"
#include "rgb_smoothing_variables.h"
#include "LEDFaces.h"



// LED strip pin
#define PIN A15
//#define PIN2           4

// 12 pixels per set
#define NUMPIXELS 36

unsigned long timer = 0;
unsigned long timer2 = 0;
int timeInterval2 = 1;
int timeInterval = 20; //the delay time between steps
int timeStep = 0; // what step are we on 0, 1, 2 ... -> 0

unsigned long pulseTimer = 0;
int pulseTimeInterval = 40;

// Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// NeoPixel faces
LEDFaces pyramid = LEDFaces();

// Variables that store color values from sensors
int R = 0;
int G = 0;
int B = 0;
// int S = 0;
// int q = 0;
int R2 = 0;
int G2 = 0;
int B2 = 0;
int R3 = 0;
int G3 = 0;
int B3 = 0;
int R4 = 0;
int G4 = 0;
int B4 = 0;
int R5 = 0;
int G5 = 0;
int B5 = 0;

int face0Brightness = 0;
int hue = 0; int sat = 0; int val = 0; int pulse = 0;
int hue2 = 0; int sat2 = 0; int val2 = 0; int pulse2 = 0;
int hue3 = 0; int sat3 = 0; int val3 = 0; int pulse3 = 0;

void setup() {
  // Proximity_controller
  // Initialize GPIO pins.
  initPins();
  // Initialize the Wire library.
  Wire.begin();

  Serial.begin(230400);
  initSensors();

  // Init smoothing values to zeros
  for (int i = 0 ; i < NUMREADINGS; i ++ ) {
    rReadings[i] = 0;
    gReadings[i] = 0;
    bReadings[i] = 0;
  }

  pyramid.begin();

  // Set Hue Color Ranges
  pyramid.setHueRanges(0,180,255);
  pyramid.setHueRanges(1,0,255);
  pyramid.setHueRanges(2,44,180);

}



void loop() {

  keepReadingSensors();

  mapSensorsToRGBS();
  mapSensorsToHSV();

  printSerial();

  smoothRGBReading();
  smoothRGB2Reading();
  smoothRGB3Reading();

  // * * * * * DrawLEDS * * * * * * *
  // pyramid.fadeInFace(0, rAverage, gAverage, bAverage);
  // pyramid.fadeInFace(1, r2Average, g2Average, b2Average);
  // pyramid.fadeInFace(2, r3Average, g3Average, b3Average);

  // * * * * * pulseFaces * * * * * * *
  pyramid.updatePulse();
  // pyramid.rotateHueOffset(1);

  // pyramid.setFaceHue(0,hue);
  pyramid.pulseFace(0, hue, sat, val, pulse);
  pyramid.pulseFace(1, hue2, sat2, val2, pulse2);
  pyramid.pulseFace(2, hue3, sat3, val3, pulse3);
  // pyramid.fastLEDTest();

  pyramid.show();

}

void mapSensorsToRGBS() {
  R = sens4;
  G = sens5;
  B = sens6;
  R2 = sens7;
  G2 = sens8;
  B2 = sens9;
  R3 = sens10;
  G3 = sens11;
  B3 = sens12;

  R = 255 - R;
  G = 255 - G;
  B = 255 - B;
  R2 = 255 - R2;
  G2 = 255 - G2;
  B2 = 255 - B2;
  R3 = 255 - R3;
  G3 = 255 - G3;
  B3 = 255 - B3;

  face0Brightness = pyramid.getFaceBrightness(0);
  printSerial();
  smoothRGBReading();
  smoothRGB2Reading();
  smoothRGB3Reading();


  //sudoPulseLEDS();
  // faces.drawLEDS(0, R,G,B);
  // faces.drawLEDS(1, R2,G2,B2);
  // faces.drawLEDS(2, R3,G3,B3);

  // faces.drawLEDS(0, rAverage, gAverage, bAverage);
  // faces.drawLEDS(1, r2Average, g2Average, b2Average);
  // faces.drawLEDS(2, r3Average, g3Average, b3Average);

  // * * * * * DrawLEDS * * * * * * *
  // faces.writeSensorLEDS(0, rAverage, gAverage, bAverage);
  // faces.writeSensorLEDS(1, r2Average, g2Average, b2Average);
  // faces.writeSensorLEDS(2, r3Average, g3Average, b3Average);

  pyramid.updatePulse();
  mapSensorsToHSV();

  pyramid.show();

}

void mapSensorsToHSV() {

  // * * * * * * * * * * * * * * * * * * * * * * * * * *
  //       1 face
  // * * * * * * * * * * * * * * * * * * * * * * * * * *

  // The max of any sensor controls pulse brightness
  pulse = maximumSensor(rAverage, gAverage, bAverage);
  // updates pulse timing sin wave
  // writeSensorLEDSHSV(face, hue, min, total)
  hue = rAverage;
  sat = gAverage;
  // The brightness is the average of the 3 sensors
  // So covering all 3 creates the brightest facegt
  val = (rAverage + gAverage + bAverage) / 3;

  // * * * * * * * * * * * * * * * * * * * * * * * * * *
  //       2 face
  // * * * * * * * * * * * * * * * * * * * * * * * * * *

  // The max of any sensor controls pulse brightness
  pulse2 = maximumSensor(r2Average, g2Average, b2Average);
  // updates pulse timing sin wave
  // faces.updatePulseHSV(1, pulse2);
  // writeSensorLEDSHSV(face, hue, min, total)
  hue2 = r2Average;
  sat2 = 255;
  // The brightness is the average of the 3 sensors
  // So covering all 3 creates the brightest facegt
  val2 = (r2Average + g2Average + b2Average) / 3;

  // * * * * * * * * * * * * * * * * * * * * * * * * * *
  //       3 face
  // * * * * * * * * * * * * * * * * * * * * * * * * * *

  // The max of any sensor controls pulse brightness
  pulse3 = maximumSensor(r3Average, g3Average, b3Average);
  // updates pulse timing sin wave
  hue3 = r3Average;
  sat3 = 255;
  // The brightness is the average of the 3 sensors
  // So covering all 3 creates the brightest facegt
  val3 = (r3Average + g3Average + b3Average) / 3;


}

void printSerial() {
  if (millis() - timer2 > timeInterval2) {
    timer2 = millis();
    Serial.println(sens1 + String(" ") + sens2 + String(" ") + sens3 + String(" ") + sens4 + String(" ") + sens5 + String(" ") + sens6 + String(" ") + sens7 + String(" ") + sens8 + String(" ") + sens9 + String(" ") + sens10 + String(" ") + sens11 + String(" ") + sens12);
    // Serial.println(rAverage + String(" ") + gAverage + String(" ") + bAverage + String(" ") + sens4 + String(" ") + sens5 + String(" ") + sens6 + String(" ") + sens7 + String(" ") + sens8 + String(" ") + sens9 + String(" ") + sens10 + String(" ") + sens11 + String(" ") + sens12);
    // Serial.println(face0Brightness);
  }
} // end Serial
void readSerial() {
  if (Serial.available()) {
    //Serial.println(String("R2 ") + R2 + String(" G2 ") + G2 + String(" B2 ") + B2);
  }
} // end Serial

int minimumSensor(int sen1, int sen2, int sen3 ) {
  // returns the smallest of the 3 input sensors
  int val = sen1;
  if (sen2 < val) {
    val = sen2;
  }
  if (sen3 < val ) {
    val = sen3;
  }
  return val;
}
int maximumSensor(int sen1, int sen2, int sen3) {
  // returns the smallest of the 3 input sensors
  int val = sen1;
  if (sen2 > val) {
    val = sen2;
  }
  if (sen3 > val ) {
    val = sen3;
  }
  return val;
}

void readRanges() {
  sens1 = readRangeResult(Add_1);
  sens2 = readRangeResult(Add_2);
  sens3 = readRangeResult(Add_3);
  sens4 = readRangeResult(Add_4);
  sens5 = readRangeResult(Add_5);
  sens6 = readRangeResult(Add_6);

  sens7 = readRangeResult(Add_7);
  sens8 = readRangeResult(Add_8);
  sens9 = readRangeResult(Add_9);
  sens10 = readRangeResult(Add_22);
  sens11 = readRangeResult(Add_23);
  sens12 = readRangeResult(Add_24);
  //    sens13 = readRangeResult(Add_10);
  //    sens14 = readRangeResult(Add_11);
  //    sens15 = readRangeResult(Add_12);
  //    sens16 = readRangeResult(Add_19);
  //    sens17 = readRangeResult(Add_20);
  //    sens18 = readRangeResult(Add_21);
}
void startRanges() {
  startRange(Add_1);
  startRange(Add_2);
  startRange(Add_3);
  startRange(Add_4);
  startRange(Add_5);
  startRange(Add_6);

  startRange(Add_7);
  startRange(Add_8);
  startRange(Add_9);
  startRange(Add_22);
  startRange(Add_23);
  startRange(Add_24);
  //    startRange(Add_10);
  //    startRange(Add_11);
  //    startRange(Add_12);
  //    startRange(Add_19);
  //    startRange(Add_20);
  //    startRange(Add_21);
}

void keepReadingSensors() {

  // timeInterval is 20 millis
  // tunes for the proximity sensors
  if (millis() - timer > timeInterval) {

    timeStep += 1;

    if (timeStep == 1) {
      //
      startRanges();
    } else if (timeStep >= 2) {
      //
      readRanges();
      timeStep = 0;
    }

    timer = millis();
  }

}

// RGB smoothing functions quick test
// Needs to be optimized

void smoothRGBReading() {
  // raw values

  gTotal = gTotal - gReadings[gReadIndex];
  gReadings[gReadIndex] = G;
  gTotal = gTotal + gReadings[gReadIndex];
  gReadIndex ++;
  if (gReadIndex >= NUMREADINGS) {
    gReadIndex = 0;
  }
  gAverage = gTotal / NUMREADINGS;

  rTotal = rTotal - rReadings[rReadIndex];
  rReadings[rReadIndex] = R;
  rTotal = rTotal + rReadings[rReadIndex];
  rReadIndex ++;
  if (rReadIndex >= NUMREADINGS) {
    rReadIndex = 0;
  }
  rAverage = rTotal / NUMREADINGS;

  bTotal = bTotal - bReadings[bReadIndex];
  bReadings[bReadIndex] = B;
  bTotal = bTotal + bReadings[bReadIndex];
  bReadIndex ++;
  if (bReadIndex >= NUMREADINGS) {
    bReadIndex = 0;
  }
  bAverage = bTotal / NUMREADINGS;
}

void smoothRGB2Reading() {
  // raw values

  g2Total = g2Total - g2Readings[g2ReadIndex];
  g2Readings[g2ReadIndex] = G2;
  g2Total = g2Total + g2Readings[g2ReadIndex];
  g2ReadIndex ++;
  if (g2ReadIndex >= NUMREADINGS) {
    g2ReadIndex = 0;
  }
  g2Average = g2Total / NUMREADINGS;

  r2Total = r2Total - r2Readings[r2ReadIndex];
  r2Readings[r2ReadIndex] = R2;
  r2Total = r2Total + r2Readings[r2ReadIndex];
  r2ReadIndex ++;
  if (r2ReadIndex >= NUMREADINGS) {
    r2ReadIndex = 0;
  }
  r2Average = r2Total / NUMREADINGS;

  b2Total = b2Total - b2Readings[b2ReadIndex];
  b2Readings[b2ReadIndex] = B2;
  b2Total = b2Total + b2Readings[b2ReadIndex];
  b2ReadIndex ++;
  if (b2ReadIndex >= NUMREADINGS) {
    b2ReadIndex = 0;
  }
  b2Average = b2Total / NUMREADINGS;
}

void smoothRGB3Reading() {
  // raw values

  g3Total = g3Total - g3Readings[g3ReadIndex];
  g3Readings[g3ReadIndex] = G3;
  g3Total = g3Total + g3Readings[g3ReadIndex];
  g3ReadIndex ++;
  if (g3ReadIndex >= NUMREADINGS) {
    g3ReadIndex = 0;
  }
  g3Average = g3Total / NUMREADINGS;

  r3Total = r3Total - r3Readings[r3ReadIndex];
  r3Readings[r3ReadIndex] = R3;
  r3Total = r3Total + r3Readings[r3ReadIndex];
  r3ReadIndex ++;
  if (r3ReadIndex >= NUMREADINGS) {
    r3ReadIndex = 0;
  }
  r3Average = r3Total / NUMREADINGS;

  b3Total = b3Total - b3Readings[b3ReadIndex];
  b3Readings[b3ReadIndex] = B3;
  b3Total = b3Total + b3Readings[b3ReadIndex];
  b3ReadIndex ++;
  if (b3ReadIndex >= NUMREADINGS) {
    b3ReadIndex = 0;
  }
  b3Average = b3Total / NUMREADINGS;
}
