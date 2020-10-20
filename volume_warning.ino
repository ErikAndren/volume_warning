#include <stdint.h>

#define UINT32_MAX 0xFFFFFFFF
#define SERIAL_DEBUG 0

const int greenPin =  3;
const int micPin = 4;
const int yellowPin = 5;
const int redPin = 6;
const int debugPin = 13;

const uint32_t NOISE_COST = 10;
const uint32_t RED_THRESHOLD = 200000;
const uint32_t YELLOW_THRESHOLD = 100000;
const uint32_t GREEN_THRESHOLD = 1;


uint32_t currentCost = 0;

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(micPin, INPUT);
  pinMode(debugPin, OUTPUT);

#if SERIAL_DEBUG
  Serial.begin(9600);
#endif
}

void loop() {
  uint32_t oldCost = currentCost;
  
  if (digitalRead(micPin) == HIGH) {
    // Prevent overflow
    if (currentCost + NOISE_COST <= UINT32_MAX) {
      currentCost += NOISE_COST;
    }

    digitalWrite(debugPin, HIGH);
  } else {
    if (currentCost) {
      currentCost--;

#if SERIAL_DEBUG
      if (currentCost == 0) {
        Serial.println(0);
      }
#endif
    }
    digitalWrite(debugPin, LOW);
  }

  if (currentCost >= RED_THRESHOLD) {
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
  } else if (currentCost >= YELLOW_THRESHOLD) {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);    
  } else if (currentCost >= GREEN_THRESHOLD) {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH); 
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);     
  }
}
