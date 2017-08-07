#include <Wire.h>
#include <VL6180X.h>


VL6180X sensor1,
	 sensor2,
	 sensor3,
	 sensor4,
	 sensor5,
	 sensor6,
	 sensor7,
	 sensor8,
	 sensor9,
	 sensor10,
	 sensor11,
	 sensor12,
	 sensor13,
	 sensor14,
	 sensor15,
	 sensor16,
	 sensor17,
	 sensor18,
	 sensor19,
	 sensor20,
	 sensor21,
	 sensor22,
	 sensor23,
	 sensor24;

int sens1;
int sens2;
int sens3;
int sens4;
int sens5;
int sens6;
int sens7;
int sens8;
int sens9;
int sens10;
int sens11;
int sens12;
int sens13;
int sens14;
int sens15;
int sens16;
int sens17;
int sens18;
int sens19;
int sens20;
int sens21;
int sens22;
int sens23;
int sens24;


int NumberOfSensors = 24;

// Initialize the GPIO pin numbers.
int GPIO_1 = 8;
int GPIO_2 = 9;
int GPIO_3 = 10;
int GPIO_4 = 11;
int GPIO_5 = 12;
int GPIO_6 = 13;
int GPIO_7 = 22;
int GPIO_8 = 23;
int GPIO_9 = 24;
int GPIO_10 = 25;
int GPIO_11 = 26;
int GPIO_12 = 27;
int GPIO_13 = 28;
int GPIO_14 = 29;
int GPIO_15 = 30;
int GPIO_16 = 31;
int GPIO_17 = 32;
int GPIO_18 = 33;
int GPIO_19 = 34;
int GPIO_20 = 35;
int GPIO_21 = 36;
int GPIO_22 = 37;
int GPIO_23 = 38;
int GPIO_24 = 39;

// Initialize the I2C Addresses.
#define Add_1 0x2A
#define Add_2 0x2B
#define Add_3 0x2C
#define Add_4 0x2D
#define Add_5 0x2E
#define Add_6 0x2F
#define Add_7 0x30
#define Add_8 0x31
#define Add_9 0x32
#define Add_10 0x33
#define Add_11 0x34
#define Add_12 0x35
#define Add_13 0x36
#define Add_14 0x37
#define Add_15 0x38
#define Add_16 0x39
#define Add_17 0x3A
#define Add_18 0x3B
#define Add_19 0x3C
#define Add_20 0x3D
#define Add_21 0x3E
#define Add_22 0x3F
#define Add_23 0x40
#define Add_24 0x41

// Sensor timer
unsigned long sensorTimer = 0;
int sensorTimeInterval = 20;
int sensorTimeStep = 0;// what step are we on 0, 1, 2 ... -> 0

void initSensors(void);
byte detectDeviceID(byte);
byte readRangeResult(byte);
byte readRangeStatus(byte);
byte setDeviceID(int, byte);
void setDeviceFreshReset(byte);
void setROASP(byte, byte);
void startRange(byte);

void readRanges9() {
  sens1 = readRangeResult(Add_1);
  sens2 = readRangeResult(Add_2);
  sens3 = readRangeResult(Add_3);
  sens4 = readRangeResult(Add_4);
  sens5 = readRangeResult(Add_5);
  sens6 = readRangeResult(Add_6);

  sens7 = readRangeResult(Add_7);
  sens8 = readRangeResult(Add_8);
  // sens9 = readRangeResult(Add_9);
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
void readRanges18() {
  sens1 = readRangeResult(Add_1);
  sens2 = readRangeResult(Add_2);
  sens3 = readRangeResult(Add_3);
  sens4 = readRangeResult(Add_4);
  sens5 = readRangeResult(Add_5);
  sens6 = readRangeResult(Add_6);

  sens7 = readRangeResult(Add_7);
  sens8 = readRangeResult(Add_8);
  // sens9 = readRangeResult(Add_9);
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
void readRanges16() {
  sens1 = readRangeResult(Add_1);
  sens2 = readRangeResult(Add_2);
  sens3 = readRangeResult(Add_3);
  sens4 = readRangeResult(Add_4);
  sens5 = readRangeResult(Add_5);
  sens6 = readRangeResult(Add_6);

  sens7 = readRangeResult(Add_7);
  sens8 = readRangeResult(Add_8);
  // sens9 = readRangeResult(Add_9);
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
void startRanges9() {
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
void startRanges18() {
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
void startRanges16() {
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

void keepReadingSensors9() {
  // timeInterval is 20 millis
  // tunes for the proximity sensors
  if (millis() - sensorTimer > sensorTimeInterval) {
    sensorTimeStep += 1;
    if (sensorTimeStep == 1) {
      startRanges9();
    } else if (sensorTimeStep >= 2) {
      readRanges9();
      sensorTimeStep = 0;
    }
    sensorTimer = millis();
  }
}
void keepReadingSensors18() {
  // timeInterval is 20 millis
  // tunes for the proximity sensors
  if (millis() - sensorTimer > sensorTimeInterval) {
    sensorTimeStep += 1;
    if (sensorTimeStep == 1) {
      startRanges18();
    } else if (sensorTimeStep >= 2) {
      readRanges18();
      sensorTimeStep = 0;
    }
    sensorTimer = millis();
  }
}
void keepReadingSensors16() {
  // timeInterval is 20 millis
  // tunes for the proximity sensors
  if (millis() - sensorTimer > sensorTimeInterval) {
    sensorTimeStep += 1;
    if (sensorTimeStep == 1) {
      startRanges16();
    } else if (sensorTimeStep >= 2) {
      readRanges16();
      sensorTimeStep = 0;
    }
    sensorTimer = millis();
  }
}

void initPins(void)
{

 digitalWrite(GPIO_1, LOW);
 digitalWrite(GPIO_2, LOW);
 digitalWrite(GPIO_3, LOW);
 digitalWrite(GPIO_4, LOW);
 digitalWrite(GPIO_5, LOW);
 digitalWrite(GPIO_6, LOW);
 digitalWrite(GPIO_7, LOW);
 digitalWrite(GPIO_8, LOW);
 digitalWrite(GPIO_9, LOW);
 digitalWrite(GPIO_10, LOW);
 digitalWrite(GPIO_11, LOW);
 digitalWrite(GPIO_12, LOW);
 digitalWrite(GPIO_13, LOW);
 digitalWrite(GPIO_14, LOW);
 digitalWrite(GPIO_15, LOW);
 digitalWrite(GPIO_16, LOW);
 digitalWrite(GPIO_17, LOW);
 digitalWrite(GPIO_18, LOW);
 digitalWrite(GPIO_19, LOW);
 digitalWrite(GPIO_20, LOW);
 digitalWrite(GPIO_21, LOW);
 digitalWrite(GPIO_22, LOW);
 digitalWrite(GPIO_23, LOW);
 digitalWrite(GPIO_24, LOW);

 delayMicroseconds(200);

 // Set the pin mode.

 pinMode(GPIO_1, OUTPUT);
 pinMode(GPIO_2, OUTPUT);
 pinMode(GPIO_3, OUTPUT);
 pinMode(GPIO_4, OUTPUT);
 pinMode(GPIO_5, OUTPUT);
 pinMode(GPIO_6, OUTPUT);
 pinMode(GPIO_7, OUTPUT);
 pinMode(GPIO_8, OUTPUT);
 pinMode(GPIO_9, OUTPUT);
 pinMode(GPIO_10, OUTPUT);
 pinMode(GPIO_11, OUTPUT);
 pinMode(GPIO_12, OUTPUT);
 pinMode(GPIO_13, OUTPUT);
 pinMode(GPIO_14, OUTPUT);
 pinMode(GPIO_15, OUTPUT);
 pinMode(GPIO_16, OUTPUT);
 pinMode(GPIO_17, OUTPUT);
 pinMode(GPIO_18, OUTPUT);
 pinMode(GPIO_19, OUTPUT);
 pinMode(GPIO_20, OUTPUT);
 pinMode(GPIO_21, OUTPUT);
 pinMode(GPIO_22, OUTPUT);
 pinMode(GPIO_23, OUTPUT);
 pinMode(GPIO_24, OUTPUT);
}

void initSensors(void)
{
 // Begin by initializing each sensor.

 // On power up, the deviceID of each sensor
 // is set to the default of 0x29. We need to
 // assign a unique deviceID to each sensor so
 // we don't have any communication conflicts.

 digitalWrite(GPIO_1, HIGH);
 delayMicroseconds(1500);
 sensor1.init();
 sensor1.setAddress(Add_1);

	 digitalWrite(GPIO_2, HIGH);
 delayMicroseconds(1500);
 sensor2.init();
 sensor2.setAddress(Add_2);

	 digitalWrite(GPIO_3, HIGH);
 delayMicroseconds(1500);
 sensor3.init();
 sensor3.setAddress(Add_3);

 digitalWrite(GPIO_4, HIGH);
 delayMicroseconds(1500);
 sensor4.init();
 sensor4.setAddress(Add_4);
//
	 digitalWrite(GPIO_5, HIGH);
 delayMicroseconds(1500);
 sensor5.init();
 sensor5.setAddress(Add_5);

		 digitalWrite(GPIO_6, HIGH);
 delayMicroseconds(1500);
 sensor6.init();
 sensor6.setAddress(Add_6);

//   7-12


		 digitalWrite(GPIO_7, HIGH);
 delayMicroseconds(1500);
 sensor7.init();
 sensor7.setAddress(Add_7);


		 digitalWrite(GPIO_8, HIGH);
 delayMicroseconds(1500);
 sensor8.init();
 sensor8.setAddress(Add_8);
//
//
		 digitalWrite(GPIO_9, HIGH);
 delayMicroseconds(1500);
 sensor9.init();
 sensor9.setAddress(Add_9);


		 digitalWrite(GPIO_22, HIGH);
 delayMicroseconds(1500);
 sensor10.init();
 sensor10.setAddress(Add_22);


		 digitalWrite(GPIO_23, HIGH);
 delayMicroseconds(1500);
 sensor11.init();
 sensor11.setAddress(Add_23);
//    \
//
digitalWrite(GPIO_24, HIGH);
 delayMicroseconds(1500);
 sensor12.init();
 sensor12.setAddress(Add_24);

//// 13-18
//

//
//
//      digitalWrite(GPIO_10, HIGH);
//  delayMicroseconds(1500);
//  sensor13.init();
//  sensor13.setAddress(Add_10);
//
//
//      digitalWrite(GPIO_11, HIGH);
//  delayMicroseconds(1500);
//  sensor14.init();
//  sensor14.setAddress(Add_11);
////
////
//      digitalWrite(GPIO_12, HIGH);
//  delayMicroseconds(1500);
//  sensor15.init();
//  sensor15.setAddress(Add_12);
//////
//////
//      digitalWrite(GPIO_19, HIGH);
//  delayMicroseconds(1500);
//  sensor16.init();
//  sensor16.setAddress(Add_19);
//
//
//      digitalWrite(GPIO_20, HIGH);
//  delayMicroseconds(1500);
//  sensor17.init();
//  sensor17.setAddress(Add_20);
//
//    digitalWrite(GPIO_21, HIGH);
//  delayMicroseconds(1500);
//  sensor18.init();
//  sensor18.setAddress(Add_21);

}

byte detectDeviceID(byte deviceID)
{
 // This function determines if
 // a device at i2CAddress responds
 // to a transmission request.

 byte error = 0xFF;

 // Begin a transmission to the device.
 Wire.beginTransmission(deviceID);
 return Wire.endTransmission();
}

byte readRangeResult(byte deviceID)
 {
	 byte rangeResult = 0x00;
	 // This function reads
	 // the range result.
	 // The RESULT_RANGE_VAL register is 0x062.
	 byte regID_High = 0x00;
	 byte regID_Low = 0x62;
	 Wire.beginTransmission(deviceID);
	 Wire.write(regID_High);
	 Wire.write(regID_Low);
	 Wire.endTransmission();

	 // Now try to get the result.
	 Wire.requestFrom(deviceID,1);

	 while(!Wire.available())
	 {
		//  Serial.println("waiting inside readRangeResult");
	 }

	 return Wire.read();
 }

 byte readRangeStatus(byte deviceID)
 {
	 // This function returns the range status.
	 // Initialize to a value that is not used.
	 byte rangeStatus = 0x8;

	 // The RESULT_RANGE_STATUS register is 0x04D.
	 byte regID_High = 0x00;
	 byte regID_Low = 0x4D;
	 Wire.beginTransmission(deviceID);
	 Wire.write(regID_High);
	 Wire.write(regID_Low);
	 Wire.endTransmission();

		// Now try to get the result.
	 Wire.requestFrom(deviceID,1);

	 while(!Wire.available())
	 {
		//  Serial.println("waiting inside readRangestatus");
	 }

	 return Wire.read();
 }

	void setDeviceFreshOutOfReset(byte deviceID)
 {
		// The Device ID register is 0x016.
		byte regID_High = 0x1;
		byte regID_Low = 0x16;
		// First send the register address.
		Wire.beginTransmission(deviceID);
		Wire.write(regID_High);
		Wire.write(regID_Low);
		Wire.write(0x00);
		Wire.endTransmission();
 }


///////////////////////////////////////////////////////
 byte setDeviceID(int GPIO_Number, byte deviceID)
 {
	 // First, set the GPIO pin high.
	 digitalWrite(GPIO_Number, HIGH);
	 // Wait for the sensor to boot up.
	 delayMicroseconds(1500);

		// The Device ID register is 0x212.
		byte regID_High = 0x2;
		byte regID_Low = 0x12;
		// First send the register address.
		// Begin transmission using default I2C address.
		Wire.beginTransmission(0x29);
		Wire.write(regID_High);
		Wire.write(regID_Low);
		// Now, send the DeviceID
		Wire.write(deviceID);
		Wire.endTransmission();
		delayMicroseconds(200);
 }

 void setROASP(byte deviceID, byte roaSamplePeriod)
 {
	 // This routine sets the READOUT_AVERAGE_SAMPLE_PERIOD.
	 Wire.beginTransmission(deviceID);
		byte regID_High = 0x01;
		byte regID_Low = 0x0A;
		Wire.write(regID_High);
		Wire.write(regID_Low);
		// Now, send the value.
		Wire.write(roaSamplePeriod);
		Wire.endTransmission();
		delayMicroseconds(200);
 }

 void startRange(byte deviceID)
 {
	 // This routine starts a single shot range conversion.

	 // The SYSRANGE_START register is at address 0x018.
	 byte regID_High = 0x00;
	 byte regID_Low = 0x18;

	 Wire.beginTransmission(deviceID);
	 Wire.write(regID_High);
	 Wire.write(regID_Low);
	 //Start single shot range measurement.
	 Wire.write(0x1);
	 Wire.endTransmission();
 }
