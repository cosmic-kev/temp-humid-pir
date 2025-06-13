/*
Default within this comment
#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
*/

#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // LED on pin 13
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // LED on
  delay(5000);                       // 0.5 s
  digitalWrite(LED_BUILTIN, LOW);   // LED off
  delay(5000);
}
