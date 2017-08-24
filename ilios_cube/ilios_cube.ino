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
#define NUMPIXELS 82

unsigned long timer = 0;
unsigned long timer2 = 0;
int timeInterval2 = 1;
int timeInterval = 20; //the delay time between steps
int timeStep = 0; // what step are we on 0, 1, 2 ... -> 0

// Call smoothing function only every 4 loop cycles
// To Increase the Decay & Attack of it
int smoothingDecayCounter = 1;
int smoothingDecayRate = 2;

unsigned long pulseTimer = 0;
int pulseTimeInterval = 40;

// Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// NeoPixel faces
LEDFaces cube = LEDFaces();

// Variables that store color values from sensors
int R = 0;
int G = 0;
int B = 0;
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
int R6 = 0;
int G6 = 0;
int B6 = 0;


int face0Brightness = 0;
int face1Brightness = 0;
int face2Brightness = 0;
int face3Brightness = 0;
int face4Brightness = 0;
int face5Brightness = 0;

int hue = 0; int sat = 0; int val = 0; int pulse = 0;
int hue2 = 0; int sat2 = 0; int val2 = 0; int pulse2 = 0;
int hue3 = 0; int sat3 = 0; int val3 = 0; int pulse3 = 0;
int hue4 = 0; int sat4 = 0; int val4 = 0; int pulse4 = 0;
int hue5 = 0; int sat5 = 0; int val5 = 0; int pulse5 = 0;
int hue6 = 0; int sat6 = 0; int val6 = 0; int pulse6 = 0;

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

  cube.begin();

  // Set Hue Color Ranges
  cube.setHueRanges(0,180,255);
  cube.setHueRanges(1,0,255);
  cube.setHueRanges(2,44,180);
  cube.setHueRanges(3,180,255);
  cube.setHueRanges(4,0,255);
  cube.setHueRanges(5,44,180);
}



void loop() {

  keepReadingSensors18();

  mapSensorsToRGBS();
  mapSensorsToHSV();

  face0Brightness = cube.getFaceBrightness(0);
  face1Brightness = cube.getFaceBrightness(1);
  face2Brightness = cube.getFaceBrightness(2);
  face3Brightness = cube.getFaceBrightness(3);
  face4Brightness = cube.getFaceBrightness(4);
  face5Brightness = cube.getFaceBrightness(5);
  printSerial();

  smoothingDecayCounter += 1;
  // Serial.println("smooth counter: ");
  // Serial.print(smoothingDecayCounter);
  if (smoothingDecayCounter % smoothingDecayRate == 0) {
    smoothRGBReading();
    smoothRGB2Reading();
    smoothRGB3Reading();
    smoothRGB4Reading();
    smoothRGB5Reading();
    smoothRGB6Reading();
    smoothingDecayCounter = 0;
  }


  // * * * * * FadeInFace * * * * * * *
  // cube.fadeInFace(0, rAverage, gAverage, bAverage);
  // cube.fadeInFace(1, r2Average, g2Average, b2Average);
  // cube.fadeInFace(2, r3Average, g3Average, b3Average);
  // cube.fadeInFace(3, r4Average, g4Average, b4Average);
  // cube.fadeInFace(4, r5Average, g5Average, b5Average);
  // cube.fadeInFace(5, r6Average, g6Average, b6Average);

  // * * * * * pulseFaces * * * * * * *
  cube.updatePulse();
  // cube.rotateHueOffset(1);

  // cube.setFaceHue(0,hue);
  cube.pulseFace(0, hue, sat, val, pulse);
  cube.pulseFace(1, hue2, sat2, val2, pulse2);
  cube.pulseFace(2, hue3, sat3, val3, pulse3);
  cube.pulseFace(3, hue4, sat4, val4, pulse4);
  cube.pulseFace(4, hue5, sat5, val5, pulse5);
  cube.pulseFace(5, hue6, sat6, val6, pulse6);

  cube.show();

}
void mapSensorsToRGBS() {
  R = sens1;
  G = sens2;
  B = sens3;
  // R = map(sens1, 0, 190, 0, 255);
  // G = map(sens2, 0, 190, 0, 255);
  // B = map(sens3, 0, 190, 0, 255);

  // R = sens1;
  // G = sens2;
  // B = sens3;
  R2 = sens4;
  G2 = sens5;
  B2 = sens6;
  R3 = sens7;
  G3 = sens8;
  B3 = sens9;

  R4 = sens10;
  G4 = sens11;
  B4 = sens12;
  R5 = sens13;
  G5 = sens14;
  B5 = sens15;
  R6 = sens16;
  G6 = sens17;
  B6 = sens18;

  R = 255 - R;
  G = 255 - G;
  B = 255 - B;
  R2 = 255 - R2;
  G2 = 255 - G2;
  B2 = 255 - B2;
  R3 = 255 - R3;
  G3 = 255 - G3;
  B3 = 255 - B3;
  R4 = 255 - R4;
  G4 = 255 - G4;
  B4 = 255 - B4;
  R5 = 255 - R5;
  G5 = 255 - G5;
  B5 = 255 - B5;
  R6 = 255 - R6;
  G6 = 255 - G6;
  B6 = 255 - B6;

  // Set the contraint and map ranges
  // The sensor lower bounds and upper bounds that will
  // then get scaled to 0 - 255 values
  int sensorLower = 0;
  int sensorUpper = 190;

  R = constrain(R, sensorLower, sensorUpper);
  G = constrain(G, sensorLower, sensorUpper);
  B = constrain(B, sensorLower, sensorUpper);
  R = map(R, sensorLower, sensorUpper, 0, 255);
  G = map(G, sensorLower, sensorUpper, 0, 255);
  B = map(B, sensorLower, sensorUpper, 0, 255);

  R2 = constrain(R2, sensorLower, sensorUpper);
  G2 = constrain(G2, sensorLower, sensorUpper);
  B2 = constrain(B2, sensorLower, sensorUpper);
  R2 = map(R2, sensorLower, sensorUpper, 0, 255);
  G2 = map(G2, sensorLower, sensorUpper, 0, 255);
  B2 = map(B2, sensorLower, sensorUpper, 0, 255);

  R3 = constrain(R3, sensorLower, sensorUpper);
  G3 = constrain(G3, sensorLower, sensorUpper);
  B3 = constrain(B3, sensorLower, sensorUpper);
  R3 = map(R3, sensorLower, sensorUpper, 0, 255);
  G3 = map(G3, sensorLower, sensorUpper, 0, 255);
  B3 = map(B3, sensorLower, sensorUpper, 0, 255);

  R4 = constrain(R4, sensorLower, sensorUpper);
  G4 = constrain(G4, sensorLower, sensorUpper);
  B4 = constrain(B4, sensorLower, sensorUpper);
  R4 = map(R4, sensorLower, sensorUpper, 0, 255);
  G4 = map(G4, sensorLower, sensorUpper, 0, 255);
  B4 = map(B4, sensorLower, sensorUpper, 0, 255);

  R5 = constrain(R5, sensorLower, sensorUpper);
  G5 = constrain(G5, sensorLower, sensorUpper);
  B5 = constrain(B5, sensorLower, sensorUpper);
  R5 = map(R5, sensorLower, sensorUpper, 0, 255);
  G5 = map(G5, sensorLower, sensorUpper, 0, 255);
  B5 = map(B5, sensorLower, sensorUpper, 0, 255);

  R6 = constrain(R6, sensorLower, sensorUpper);
  G6 = constrain(G6, sensorLower, sensorUpper);
  B6 = constrain(B6, sensorLower, sensorUpper);
  R6 = map(R6, sensorLower, sensorUpper, 0, 255);
  G6 = map(G6, sensorLower, sensorUpper, 0, 255);
  B6 = map(B6, sensorLower, sensorUpper, 0, 255);

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
  sat = 255;
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

  // * * * * * * * * * * * * * * * * * * * * * * * * * *
  //       4 face
  // * * * * * * * * * * * * * * * * * * * * * * * * * *

  // The max of any sensor controls pulse brightness
  pulse4 = maximumSensor(r4Average, g4Average, b4Average);
  // updates pulse timing sin wave
  hue4 = r4Average;
  sat4 = 255;
  // The brightness is the average of the 3 sensors
  // So covering all 3 creates the brightest facegt
  val4 = (r4Average + g4Average + b4Average) / 3;
  // * * * * * * * * * * * * * * * * * * * * * * * * * *
  //       5 face
  // * * * * * * * * * * * * * * * * * * * * * * * * * *

  // The max of any sensor controls pulse brightness
  pulse5 = maximumSensor(r5Average, g5Average, b5Average);
  // updates pulse timing sin wave
  hue5 = r5Average;
  sat5 = 255;
  // The brightness is the average of the 3 sensors
  // So covering all 3 creates the brightest facegt
  val5 = (r5Average + g5Average + b5Average) / 3;
  // * * * * * * * * * * * * * * * * * * * * * * * * * *
  //       6 face
  // * * * * * * * * * * * * * * * * * * * * * * * * * *

  // The max of any sensor controls pulse brightness
  pulse6 = maximumSensor(r6Average, g6Average, b6Average);
  // updates pulse timing sin wave
  hue6 = r6Average;
  sat6 = 255;
  // The brightness is the average of the 3 sensors
  // So covering all 3 creates the brightest facegt
  val6 = (r6Average + g6Average + b6Average) / 3;

}

void printSerial() {
  if (millis() - timer2 > timeInterval2) {
    timer2 = millis();
    // Serial.println(sens1 + String(" ") + sens2 + String(" ") + sens3 + String(" ") + sens4 + String(" ") + sens5 + String(" ") + sens6 + String(" ") + sens7 + String(" ") + sens8 + String(" ") + sens9 + String(" ") + sens10 + String(" ") + sens11 + String(" ") + sens12 + String(" ") + sens13 + String(" ") + sens14 + String(" ") + sens15 + String(" ") + sens16 + String(" ") + sens17 + String(" ") + sens18);
    // Serial.println(rAverage + String(" ") + gAverage + String(" ") + bAverage + String(" ") + sens4 + String(" ") + sens5 + String(" ") + sens6 + String(" ") + sens7 + String(" ") + sens8 + String(" ") + sens9 + String(" ") + sens10 + String(" ") + sens11 + String(" ") + sens12);
    // Serial.println(R + String(" ") + G + String(" ") + B);
    Serial.println(face0Brightness + String(" ") + face1Brightness + String(" ") + face2Brightness + String(" ") + face3Brightness + String(" ") + face4Brightness + String(" ") + face5Brightness);
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
void smoothRGB4Reading() {
  // raw values

  g4Total = g4Total - g4Readings[g4ReadIndex];
  g4Readings[g4ReadIndex] = G4;
  g4Total = g4Total + g4Readings[g4ReadIndex];
  g4ReadIndex ++;
  if (g4ReadIndex >= NUMREADINGS) {
    g4ReadIndex = 0;
  }
  g4Average = g4Total / NUMREADINGS;

  r4Total = r4Total - r4Readings[r4ReadIndex];
  r4Readings[r4ReadIndex] = R4;
  r4Total = r4Total + r4Readings[r4ReadIndex];
  r4ReadIndex ++;
  if (r4ReadIndex >= NUMREADINGS) {
    r4ReadIndex = 0;
  }
  r4Average = r4Total / NUMREADINGS;

  b4Total = b4Total - b4Readings[b4ReadIndex];
  b4Readings[b4ReadIndex] = B4;
  b4Total = b4Total + b4Readings[b4ReadIndex];
  b4ReadIndex ++;
  if (b4ReadIndex >= NUMREADINGS) {
    b4ReadIndex = 0;
  }
  b4Average = b4Total / NUMREADINGS;
}
void smoothRGB5Reading() {
  // raw values

  g5Total = g5Total - g5Readings[g5ReadIndex];
  g5Readings[g5ReadIndex] = G5;
  g5Total = g5Total + g5Readings[g5ReadIndex];
  g5ReadIndex ++;
  if (g5ReadIndex >= NUMREADINGS) {
    g5ReadIndex = 0;
  }
  g5Average = g5Total / NUMREADINGS;

  r5Total = r5Total - r5Readings[r5ReadIndex];
  r5Readings[r5ReadIndex] = R5;
  r5Total = r5Total + r5Readings[r5ReadIndex];
  r5ReadIndex ++;
  if (r5ReadIndex >= NUMREADINGS) {
    r5ReadIndex = 0;
  }
  r5Average = r5Total / NUMREADINGS;

  b5Total = b5Total - b5Readings[b5ReadIndex];
  b5Readings[b5ReadIndex] = B5;
  b5Total = b5Total + b5Readings[b5ReadIndex];
  b5ReadIndex ++;
  if (b5ReadIndex >= NUMREADINGS) {
    b5ReadIndex = 0;
  }
  b5Average = b5Total / NUMREADINGS;
}
void smoothRGB6Reading() {
  // raw values

  g6Total = g6Total - g6Readings[g6ReadIndex];
  g6Readings[g6ReadIndex] = G6;
  g6Total = g6Total + g6Readings[g6ReadIndex];
  g6ReadIndex ++;
  if (g6ReadIndex >= NUMREADINGS) {
    g6ReadIndex = 0;
  }
  g6Average = g6Total / NUMREADINGS;

  r6Total = r6Total - r6Readings[r6ReadIndex];
  r6Readings[r6ReadIndex] = R6;
  r6Total = r6Total + r6Readings[r6ReadIndex];
  r6ReadIndex ++;
  if (r6ReadIndex >= NUMREADINGS) {
    r6ReadIndex = 0;
  }
  r6Average = r6Total / NUMREADINGS;

  b6Total = b6Total - b6Readings[b6ReadIndex];
  b6Readings[b6ReadIndex] = B6;
  b6Total = b6Total + b6Readings[b6ReadIndex];
  b6ReadIndex ++;
  if (b6ReadIndex >= NUMREADINGS) {
    b6ReadIndex = 0;
  }
  b6Average = b6Total / NUMREADINGS;
}
