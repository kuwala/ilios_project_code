//Smoothing Test

// Samples read for the average function
#define NUMREADINGS 100

class AverageSmoother  {
public:
  int readings[NUMREADINGS];
  int total = 0;
  int readIndex = 0;
  int average = 0;

  AverageSmoother() {
    for (size_t i = 0; i < NUMREADINGS; i++) {
      readings[i] = 0;
    }
    int total = 0;
    int readIndex = 0;
    int average = 0;
  }
  int getCurrentSmooth() {
    return average;
  }
  int newReading(int newValue) {
    // calculates new average smooth value

    readings[readIndex] = newValue;
    total = total + readings[readIndex];
    readIndex ++;
    if (readIndex >= NUMREADINGS) {
      readIndex = 0;
    }
    // returns new average
    average = total / NUMREADINGS;
    return average;
  }

};

// Face 1
int gReadings[NUMREADINGS];
int gTotal = 0;
int gReadIndex = 0;
int gAverage = 0;

int bReadings[NUMREADINGS];
int bTotal = 0;
int bReadIndex = 0;
int bAverage = 0;

int rReadings[NUMREADINGS];
int rTotal = 0;
int rReadIndex = 0;
int rAverage = 0;

// Face 2

int g2Readings[NUMREADINGS];
int g2Total = 0;
int g2ReadIndex = 0;
int g2Average = 0;

int b2Readings[NUMREADINGS];
int b2Total = 0;
int b2ReadIndex = 0;
int b2Average = 0;

int r2Readings[NUMREADINGS];
int r2Total = 0;
int r2ReadIndex = 0;
int r2Average = 0;

// Face 3

int g3Readings[NUMREADINGS];
int g3Total = 0;
int g3ReadIndex = 0;
int g3Average = 0;

int b3Readings[NUMREADINGS];
int b3Total = 0;
int b3ReadIndex = 0;
int b3Average = 0;

int r3Readings[NUMREADINGS];
int r3Total = 0;
int r3ReadIndex = 0;
int r3Average = 0;
