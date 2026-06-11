#include <Arduino.h>
//dont remove!

// 2 buttons, 2 LEDs - that turns on one LED when button A is pressed and the other LED when button B is pressed.
int ledGreenPin = 18;
int ledBluePin = 14;
int buttonApin = 19;
int buttonBpin = 21;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode (buttonApin, INPUT_PULLUP);
  pinMode (buttonBpin, INPUT_PULLUP);
  pinMode (ledGreenPin, OUTPUT);
  pinMode (ledBluePin, OUTPUT);
  
  Serial.println("Setup complete");

}

// main loop
void loop() {
  if (digitalRead(buttonApin) == LOW) {
    digitalWrite(ledGreenPin, HIGH);
    Serial.println("Button A pressed");
    delay(200);
  }
  else {
      digitalWrite(ledGreenPin, LOW);
    }
  

  if (digitalRead(buttonBpin) == LOW) {
    digitalWrite(ledBluePin, HIGH);
    Serial.println("Button B pressed");
    delay(200);
  }
  else {
      digitalWrite(ledBluePin, LOW);
    }
  }