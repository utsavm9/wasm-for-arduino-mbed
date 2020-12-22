
#include "arduino_api.h"

int LED_BUILTIN;
unsigned long startTime, endTime;


void setup() {
  LED_BUILTIN = getPinLED();
  char* c = (char*) malloc(10);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  startTime = millis();
  fib(24);
  endTime = millis();
  unsigned long elapsedTime = endTime - startTime;

}

// the loop function runs over and over again forever
void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(100);                        // wait 100ms
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(100);                        // wait 900ms
  // print("Hello world\n");
  // delay(800);
}

unsigned long fib(int n) {
  if (n < 2)
    return n;
  return fib(n-1) + fib(n-2);
}

/*
 * Entry point
 */

WASM_EXPORT
void _start() {
  setup();
  // while (1) { loop(); }
}
