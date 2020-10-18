#include <stdint.h>
#include <limits.h>

const int greenPin =  3;
const int micPin = 4;
const int yellowPin = 5;
const int redPin = 6;
const int debugPin = 13;

const uint32_t NOISE_COST = 1000;
const uint32_t RED_THRESHOLD = 1000000;
const uint32_t YELLOW_THRESHOLD = 500000;
const uint32_t GREEN_THRESHOLD = 100000;

unsigned int currentCost = 0;

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(micPin, INPUT);
  pinMode(debugPin, OUTPUT);
}

void loop() {
  if (digitalRead(micPin) == HIGH) {
    // Prevent overflow
    if (currentCost + NOISE_COST < INT_MAX) {
      currentCost += NOISE_COST;    
    }

    digitalWrite(debugPin, HIGH);
  } else {
    if (currentCost) {
      currentCost--;
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
