#include <psx-controller.h>

#define dataPin 8
#define cmndPin 9
#define attPin 11
#define clockPin 10
#define ackPin 2
#define LEDPin 13

PSXController controller;

void setup() {
  controller.setupPins(dataPin, cmndPin, attPin, clockPin, LEDPin, ackPin, 0);
  controller.set(psxX | psxLeft | psxL2);
  Serial.begin(9600);
}

void loop() {
  Serial.println(controller.tick());
}
