#include <Arduino.h>
//dont remove!

// 2 buttons, 1 LED - that turns on when button A is pressed and turns off when button B is pressed.
int ledPin = 18;
int buttonApin = 19;
int buttonBpin = 21;

void setup() {
  pinMode (buttonApin, INPUT_PULLUP);
  pinMode (buttonBpin, INPUT_PULLUP);
  pinMode (ledPin, OUTPUT);

}

// main loop
void loop() {
if (digitalRead(buttonApin)== LOW)
{
  digitalWrite (ledPin, HIGH);
}
if (digitalRead(buttonBpin)== LOW)
{
  digitalWrite (ledPin, LOW);
}
}