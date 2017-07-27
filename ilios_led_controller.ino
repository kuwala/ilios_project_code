/*
 *  ilios project led controller
 *  by Jonathon Mooney
 *  code by Jonathon Mooney, Daniel Smolentsev
 *
 *  code description:
 *  the led controller receives serial data (from a max patch) in a string format [ r g b r2 g2 b2 r3 g3 b3 ... ]
 *  each set of rgb values is then pushed to the neopixel rings on each side.
 *
 *
 */

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "ilios_proximity_controller.h"


// LED strip pin
#define PIN          3
//#define PIN2           4

#define NUMPIXELS 80

unsigned long timer = 0;
int timeInterval = 100;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

// Variables that store color values from sensors
int R = 0;
int G = 0;
int B = 0;
int S = 0;
int q = 0;
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

void setup() {

  Serial.begin(9600);

  // Initialize pixel strips
  // pixels.setBrightness(64);
  pixels.begin();

   // pixels2.begin();
   Serial.print("ilios_led_controller starting");


  // Proximity_controller
  // Initialize GPIO pins.
 initPins();

  // Initialize the Wire library.
  Wire.begin();
}

void loop() {

  sensorLoop();
  /*
  readSerial();
  //delay(100);
  drawLEDS(R2,G2,B2);
  //updateLEDS();
  */

}

void readSerial() {

    if(Serial.available()) {


    R2 = Serial.read();
    G2 = Serial.read();
    B2 = Serial.read();
//    R = Serial.read();
//    G = Serial.read();
//    B = Serial.read();
//    R3 = Serial.read();
//    G3 = Serial.read();
//    B3 = Serial.read();
//    R4 = Serial.read();
//    G4 = Serial.read();
//    B4 = Serial.read();
//    R5 = Serial.read();
//    G5 = Serial.read();
//    B5 = Serial.read();

    if(R2 == -1) {
      R2 = 0;
    }

    if(B2 == -1) {
      B2 = 0;
    }

    if(G2 == -1) {
      G2 = 0;

    }
    //Serial.println(String("R2 ") + R2 + String(" G2 ") + G2 + String(" B2 ") + B2);
  }

}
void updateLEDS() {
  // Timer base draw leds
  // This will be useful if we want to incorporate animations or multi led patterns
  if (millis() - timer > timeInterval) {
    //randomLEDS();
    timer = millis();
  }
  Serial.println("updating leds");
}

void drawLEDS(int r, int g, int b) {
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(r, g, b));

  }

  pixels.show();


}
