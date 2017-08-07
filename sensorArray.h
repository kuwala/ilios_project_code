#define NUM_SENSORS 18
#define NUM_READINGS 100
class SensorArray {
  int values[NUM_SENSORS];
  int totals[NUM_SENSORS];
  int indexs[NUM_SENSORS];
  int readings[NUM_SENSORS][NUM_READINGS];
  int averages[NUM_SENSORS];

  unsigned long timer;
  int timerInterval;
  SensorArray() {

    for (size_t i = 0; i < NUM_SENSORS; i++) {
      values[i] = 0;
    }

  }
  void updateAverage(int sensorNum, int newValue) {
    // subtract last indexed value from totals
    totals[sensorNum] =  totals[sensorNum] - readings[sensorNum][indexs[sensorNum]];
    // set new value in that place
    readings[sensorNum][indexs[sensorNum]] = newValue;
    // add new v
    totals[sensorNum] = totals[sensorNum] + readings[sensorNum][indexs[sensorNum]];
    indexs[sensorNum] ++;
    if (indexs[sensorNum] >= NUMREADINGS) {
      indexs[sensorNum] = 0;
    }
    averages[sensorNum] = totals[sensorNum] / NUM_READINGS;
  }
  // void DummySensors() {
  //   timer = 0;
  //   timerInterval = 100;
  //   for (size_t i = 0; i < NUM_SENSORS; i++) {
  //     sensorValues[i] = 0;
  //   }
  // }
  void update () {
    // generate random values in sensors
    if (millis() - timer > timerInterval) {
      for (size_t i = 0; i < NUM_SENSORS; i++) {
        // increment(i);
      }
    }

  }
  // void randomize(int i) {
  //   // for testing
  //   sensorValues[i] = random(255);
  // }
  // void increment(int i) {
  //   // For testing
  //   sensorValues[i] = (sensorValues[i] + 1) % 255;
  // }

};
