#define NUM_SENSORS
class SensorArray {
  int sensorValues[NUM_SENSORS];
  unsigned long timer;
  int timerInterval;
  DummySensors() {
    timer = 0;
    timerInterval = 100;
    for (size_t i = 0; i < NUM_SENSORS; i++) {
      sensorValues[i] = 0;
    }
  }
  void update () {
    // generate random values in sensors
    if (millis() - timer > timerInterval) {
      for (size_t i = 0; i < NUM_SENSORS; i++) {
        increment(i);
      }
    }

  }
  void randomize(int i) {
    // for testing
    sensorValues[i] = random(255);
  }
  void increment(int i) {
    // For testing
    sensorValues[i] = (sensorValues[i] + 1) % 255;
  }

};
