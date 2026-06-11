#include <Arduino.h>
//dont remove!

// #define or int variables here

#include <ESP32Servo.h>

Servo myservo; //servo object

//servo: Red on 3v3, Brown on GND, Orange on GPIO 18
void setup() {
    myservo.attach(18);
    myservo.write(90);  //set servo to middle position
}

void loop() {
    myservo.write(0);
    delay(1000);
    myservo.write(90);
    delay(1000);
    myservo.write(180);
    delay(1000);
    myservo.write(90);
    delay(1000);
}