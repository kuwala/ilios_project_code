// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
int one = 1;

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN          3
//#define PIN2           4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      80

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

 // delay for half a second

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

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  Serial.begin(230400);
  pixels.begin();
   // pixels2.begin();// This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

if(Serial.available()) {
  

  R2 = Serial.read();
 // delay(5);
//  G2 = Serial.read();
////  delay(5);
//  B2 = Serial.read();
//  delay(5);
//  R = Serial.read();
//  G = Serial.read();
//  B = Serial.read();
//  R3 = Serial.read();
//  G3 = Serial.read();
//  B3 = Serial.read();
//  R4 = Serial.read();
//  G4 = Serial.read();
//  B4 = Serial.read();
//  R5 = Serial.read();
//  G5 = Serial.read();
//  B5 = Serial.read();
//
//
  if(R2 == -1) {
    R2 = 0;
  }

  if(B2 == -1) {
    B2 = 0;
  }

  if(G2 == -1) {
    G2 = 0;
   
  }

//    if(R == -1) {
//    R = 0;
//  }
//
//  if(B == -1) {
//    B = 0;
//  }
//
//  if(G == -1) {
//    G = 0;
//   
//  }
//  S = Serial.read();

//  Serial.println("S"); Serial.println(S);
  Serial.println("R2"); Serial.println(R2);
//  Serial.println("G2"); Serial.println(G2);
//  Serial.println("B2"); Serial.println(B2);
  // delay(10);
 //  Serial.println(String("R2 ") + R2 + String(" G2 ") + G2 + String(" B2 ") + B2);


  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  //  if(abs(R2-R)<10 && abs(G2-G)<10 && abs(B2-B)<10) {
   // pixels1 = Adafruit_NeoPixel(5, 1, NEO_GRB + NEO_KHZ800);
    pixels.setPixelColor(i, pixels.Color(R2,G2,B2)); // Moderately bright green color.
  
  pixels.show();
// pixels2 = Adafruit_NeoPixel(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800);
//   pixels2.setPixelColor(i, pixels2.Color(R,G,B)); // Moderately bright green color.
//  pixels2.show();
//   pixels.setPixelColor(i, pixels.Color(R3,G3,B3)); // Moderately bright green color.
//  pixels.show();
//   pixels.setPixelColor(i, pixels.Color(R4,G4,B4)); // Moderately bright green color.
//  pixels.show();
//   pixels.setPixelColor(i, pixels.Color(R5,G5,B5)); // Moderately bright green color.
//  pixels.show(); 


  }
}
}
