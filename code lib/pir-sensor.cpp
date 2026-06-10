#include <Arduino.h>
//dont remove!

// #define or int variables here

int ledPin = 19;
int pirPin = 18;
int pirValue;

//setup code, runs once at startup
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
}


//loop code, runs repeatedly after setup
void loop() {
  pirValue = digitalRead(pirPin);
  if (pirValue == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
  }
  if (pirValue == LOW) {
    digitalWrite(ledPin, LOW);
  }
}
