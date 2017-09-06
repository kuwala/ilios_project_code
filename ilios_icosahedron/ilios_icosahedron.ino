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
#define NUMPIXELS 120
// 0 - 1 value ranges
// smaller values are
// take more time
#define EASEINMOD 0.1
#define EASEOUTMOD 0.008
#define EASEOUTMODSERIAL 0.1


unsigned long timer = 0;
unsigned long timer2 = 0;
int timeInterval2 = 1;
int timeInterval = 20; //the delay time between steps
int timeStep = 0; // what step are we on 0, 1, 2 ... -> 0

unsigned long pulseTimer = 0;
int pulseTimeInterval = 40;

// Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// NeoPixel faces
LEDFaces icosahedron = LEDFaces();

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

// Sensors serial out
int rSerialOut = 0;
int gSerialOut = 0;
int bSerialOut = 0;

int r2SerialOut = 0;
int g2SerialOut = 0;
int b2SerialOut = 0;

int r3SerialOut = 0;
int g3SerialOut = 0;
int b3SerialOut = 0;

int r4SerialOut = 0;
int g4SerialOut = 0;
int b4SerialOut = 0;

int r5SerialOut = 0;
int g5SerialOut = 0;
int b5SerialOut = 0;

int r6SerialOut = 0;
int g6SerialOut = 0;
int b6SerialOut = 0;


int face0Brightness = 0;
int face1Brightness = 0;
int face2Brightness = 0;
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

  icosahedron.begin();

  // Set Hue Color Ranges for the faces
  icosahedron.setHueRanges(0, 96,255);
  icosahedron.setHueRanges(1, 96, 160);
  icosahedron.setHueRanges(2, 160, 224);
  icosahedron.setHueRanges(3, 224, 44);
  icosahedron.setHueRanges(4, 44,180);
  icosahedron.setHueRanges(5,180,255);
  icosahedron.setHueRanges(6, 0,160);
  icosahedron.setHueRanges(7,96,180);
  icosahedron.setHueRanges(8,0,255);
  icosahedron.setHueRanges(9,255,0);
  icosahedron.setHueRanges(10,0,192);
  icosahedron.setHueRanges(11,64,180);
  icosahedron.setHueRanges(12,170,82);
  icosahedron.setHueRanges(13,170,0);
  icosahedron.setHueRanges(14,224,160);
  icosahedron.setHueRanges(15,96,0);

  icosahedron.setSaturation(12, 200);

}



void loop() {

  keepReadingSensors18();

  mapSensorsToRGBS();
  mapSensorsToHSV();

  printSerial();
  face0Brightness = icosahedron.getFaceBrightness(0);
  face1Brightness = icosahedron.getFaceBrightness(1);
  face2Brightness = icosahedron.getFaceBrightness(2);

  // smoothRGBReading();
  // smoothRGB2Reading();
  // smoothRGB3Reading();
  // smoothRGB4Reading();
  // smoothRGB5Reading();
  // smoothRGB6Reading();
  easeSensors();

  // * * * * * DrawLEDS * * * * * * *
  // icosahedron.fadeInFace(0, rAverage, gAverage, bAverage);
  // icosahedron.fadeInFace(1, r2Average, g2Average, b2Average);
  // icosahedron.fadeInFace(2, r3Average, g3Average, b3Average);

  // icosahedron is using the r g b sensor values independently
  // so each face gets 1 r or 1 g or one b average value that it
  // then scales its hue and brightness with


  icosahedron.fadeInIcosaFace(0, rAverage);
  icosahedron.fadeInIcosaFace(2, bAverage); // Face 2 has sensor 3
  icosahedron.fadeInIcosaFace(1, gAverage); // Face 3 has sensor 2

  icosahedron.fadeInIcosaFace(3, r2Average);
  icosahedron.fadeInIcosaFace(4, g2Average);
  icosahedron.fadeInIcosaFace(5, b2Average);

  icosahedron.fadeInIcosaFace(6, r3Average);
  icosahedron.fadeInIcosaFace(7, g3Average);
  icosahedron.fadeInIcosaFace(8, b3Average);

  icosahedron.fadeInIcosaFace(9, r4Average);
  icosahedron.fadeInIcosaFace(10, g4Average);
  icosahedron.fadeInIcosaFace(11, b4Average);

  icosahedron.fadeInIcosaFace(12, r5Average);
  icosahedron.fadeInIcosaFace(13, g5Average);
  icosahedron.fadeInIcosaFace(14, b5Average);

  // Face 16 has sensor 17 (g6)
  icosahedron.fadeInIcosaFace(15, g6Average);

  // 17 and 18 not used
  // icosahedron.fadeInIcosaFace(16, g6Average);
  // icosahedron.fadeInIcosaFace(17, b6Average);

  // * * * * * pulseFaces * * * * * * *
  icosahedron.updatePulse();
  // icosahedron.rotateHueOffset(1);

  // icosahedron.setFaceHue(0,hue);
  // icosahedron.pulseFace(0, hue, sat, val, pulse);
  // icosahedron.pulseFace(1, hue2, sat2, val2, pulse2);
  // icosahedron.pulseFace(2, hue3, sat3, val3, pulse3);
  // icosahedron.fastLEDTest();

  icosahedron.show();

}
float easeInOut(float currentSensorValue, float targetSensorValue) {
  // Needs to be a number between 0 - 1
  // Lower number is more easeing and takes longer
  // for the sensor to get to its intended value
  float easeInModifier = EASEINMOD; // quicker attack
  float easeOutModifier = EASEOUTMOD; // slower decay
  float easeAmount = 0;
  if ( (targetSensorValue - currentSensorValue ) > 0) {
    // easeIn
    easeAmount = (targetSensorValue - currentSensorValue) * easeInModifier;
  } else {
    // easeOut
    easeAmount = (targetSensorValue - currentSensorValue) * easeOutModifier;
  }

  float smoothedSensor = currentSensorValue + easeAmount;
  return smoothedSensor;
}

float easeInOutSerial(float currentSensorValue, float targetSensorValue) {
  // Needs to be a number between 0 - 1
  // Lower number is more easeing and takes longer
  // for the sensor to get to its intended value
  float easeInModifier = EASEINMOD; // quicker attack
  float easeOutModifier = EASEOUTMODSERIAL; // slower decay
  float easeAmount = 0;
  if ( (targetSensorValue - currentSensorValue ) > 0) {
    // easeIn
    easeAmount = (targetSensorValue - currentSensorValue) * easeInModifier;
  } else {
    // easeOut
    easeAmount = (targetSensorValue - currentSensorValue) * easeOutModifier;
  }

  float smoothedSensor = currentSensorValue + easeAmount;
  return smoothedSensor;
}
void easeSensors() {
  // Ease in and out each sensor value
  // With a seperat speed of easing in and out
  // Like an Attack / Decay
  // Stores the eased values into the rgb Average variables
  // the whole sensor code preforably needs to be refactored
  rAverage = easeInOut(rAverage, R);
  gAverage = easeInOut(gAverage, G);
  bAverage = easeInOut(bAverage, B);

  r2Average = easeInOut(r2Average, R2);
  g2Average = easeInOut(g2Average, G2);
  b2Average = easeInOut(b2Average, B2);

  r3Average = easeInOut(r3Average, R3);
  g3Average = easeInOut(g3Average, G3);
  b3Average = easeInOut(b3Average, B3);

  r4Average = easeInOut(r4Average, R4);
  g4Average = easeInOut(g4Average, G4);
  b4Average = easeInOut(b4Average, B4);

  r5Average = easeInOut(r5Average, R5);
  g5Average = easeInOut(g5Average, G5);
  b5Average = easeInOut(b5Average, B5);

  r6Average = easeInOut(r6Average, R6);
  g6Average = easeInOut(g6Average, G6);
  b6Average = easeInOut(b6Average, B6);
  // seperate serial out eased
  rSerialOut = easeInOutSerial(rSerialOut, R);
  gSerialOut = easeInOutSerial(gSerialOut, G);
  bSerialOut = easeInOutSerial(bSerialOut, B);

  r2SerialOut = easeInOutSerial(r2SerialOut, R2);
  g2SerialOut = easeInOutSerial(g2SerialOut, G2);
  b2SerialOut = easeInOutSerial(b2SerialOut, B2);

  r3SerialOut = easeInOutSerial(r3SerialOut, R3);
  g3SerialOut = easeInOutSerial(g3SerialOut, G3);
  b3SerialOut = easeInOutSerial(b3SerialOut, B3);

  r4SerialOut = easeInOutSerial(r4SerialOut, R4);
  g4SerialOut = easeInOutSerial(g4SerialOut, G4);
  b4SerialOut = easeInOutSerial(b4SerialOut, B4);

  r5SerialOut = easeInOutSerial(r5SerialOut, R5);
  g5SerialOut = easeInOutSerial(g5SerialOut, G5);
  b5SerialOut = easeInOutSerial(b5SerialOut, B5);

  r6SerialOut = easeInOutSerial(r6SerialOut, R6);
  g6SerialOut = easeInOutSerial(g6SerialOut, G6);
  b6SerialOut = easeInOutSerial(b6SerialOut, B6);
}

void mapSensorsToRGBS() {
  R = sens1;
  G = sens2;
  B = sens3;
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
    // Serial.println(sens1 + String(" ") + sens2 + String(" ") + sens3 + String(" ") + sens4 + String(" ") + sens5 + String(" ") + sens6 + String(" ") + sens7 + String(" ") + sens8 + String(" ") + sens9 + String(" ") + sens10 + String(" ") + sens11 + String(" ") + sens12);

    // old smoothed serial
    // Serial.println(rAverage + String(" ") + gAverage + String(" ") + bAverage + String(" ") + r2Average + String(" ") + g2Average + String(" ") + b2Average + String(" ")
    //  + r3Average + String(" ") + g3Average + String(" ") + b3Average + String(" ") + r4Average + String(" ") + g4Average + String(" ") + b4Average + String(" ")
    //  + r5Average + String(" ") + g5Average + String(" ") + b5Average + String(" ") + r6Average + String(" ") + g6Average + String(" ") + b6Average + String(" "));

    Serial.println(rSerialOut + String(" ") + gSerialOut + String(" ") + bSerialOut + String(" ") + r2SerialOut + String(" ") + g2SerialOut + String(" ") + b2SerialOut + String(" ")
     + r3SerialOut + String(" ") + g3SerialOut + String(" ") + b3SerialOut + String(" ") + r4SerialOut + String(" ") + g4SerialOut + String(" ") + b4SerialOut + String(" ")
     + r5SerialOut + String(" ") + g5SerialOut + String(" ") + b5SerialOut + String(" ") + r6SerialOut + String(" ") + g6SerialOut + String(" ") + b6SerialOut + String(" "));
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
