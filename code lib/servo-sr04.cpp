#include <Arduino.h>
//dont remove!

// servo moves based on distance measured by SR04ultrasonic sensor

//setup - servo: Red on 3v3, Brown on GND, Orange on GPIO 23
//Sensor TRIG_PIN 5
//Sensor ECHO_PIN 18 

#include <SR04.h>

//sensor object
#define TRIG_PIN 5
#define ECHO_PIN 18

// servo object
#include <ESP32Servo.h>
Servo myservo; //servo object

//servo: Red on 3v3, Brown on GND, Orange on GPIO 23
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;


void setup() {
   Serial.begin(115200);
   delay(1000);
   myservo.attach(23);
}

void loop() {
   a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
    // servo position based on distance
    if (a <= 10) {
        myservo.write(0);
        delay(500);
    } else if (a <= 25) {
        myservo.write(40);
        delay(500);
    } else if (a <= 50) {
        myservo.write(90);
        delay(500);
    } else if (a <= 75) {
        myservo.write(135);
        delay(500);
    } else if (a <= 100) {
        myservo.write(180);
        delay(500);
    } else {
        myservo.write(180);
        delay(500);
    }
}