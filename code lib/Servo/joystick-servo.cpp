#include <Arduino.h>
#include <ESP32Servo.h>

//Servo: Red on 3v3, Brown on GND, Orange on GPIO 21, 
//Analog Joystick: VRx on 34, VRy on 35, and SW on 18, 3v3+gnd
const int SW_pin = 18;
const int X_pin = 34;
const int Y_pin = 35; 

Servo myservo; //servo object


int readSmooth(int pin) {
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += analogRead(pin);
        delay(2);
    }
    return total / 5;
}


void setup() {
    myservo.attach(21);
    myservo.write(90);  //set servo to middle position
    pinMode(SW_pin, INPUT_PULLUP);
    Serial.begin(115200);
}


//loop code, runs repeatedly after setup
void loop() {
    Serial.print("Switch: ");

    Serial.print(digitalRead(SW_pin));
    
    Serial.print("\n");
    Serial.print("X-axis: ");

  Serial.print(analogRead(X_pin));
 //linear conversion function (map) 
 //joystick value from 0–4095 and convert it into 0–180 degrees - So: 0 → 0° , 2048 → ~90° , 4095 → 180°
    int x = readSmooth(X_pin);
    int angle = map(x, 0, 4095, 0, 180);
    myservo.write(angle);

  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  delay(10);
}