#include <Arduino.h>

// 3 LEDS and 2 Buttons: Button 1 switches the LED, while button 2 powers the LED
 
int led1 = 26;
int led2 = 25;
int led3 = 33;
int button1 = 21;
int button2 = 19;

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode (button1, INPUT_PULLUP);
    pinMode (button2, INPUT_PULLUP);
    pinMode (led1, OUTPUT);
    pinMode (led2, OUTPUT);
    pinMode (led3, OUTPUT);
    Serial.println("Init Complete");
}

// button 1 switches between the 3 leds 
int ledswitch = 1;

void loop() {

    if (digitalRead(button1)==LOW) {
        ledswitch++;
        if (ledswitch > 3) ledswitch =1;
        Serial.println("Switched LED");
        delay(200);
    }
    
    switch (ledswitch) {
        
        case 1:
        if (digitalRead(button2)==LOW) {
            digitalWrite(led1, HIGH);
            Serial.println("Button Pressed");
            delay(200);
        } else {
            digitalWrite(led1, LOW);
        } 
        break;
    
        case 2:
        if (digitalRead(button2)==LOW) {
            digitalWrite(led2, HIGH);
            Serial.println("Button Pressed");
            delay(200);
        } else {
            digitalWrite(led2, LOW);
        }
        break;
    
        case 3:
        if (digitalRead(button2)==LOW) {
            digitalWrite(led3, HIGH);
            Serial.println("Button Pressed");
            delay(200);
        } else {
            digitalWrite(led3, LOW);
        }
            break;
    
    }
}


// This was the init loop, button 1 powered one led1, button 2 powered led2, pressing both buttons powered led3


// void loop() {
    
//     if (digitalRead(button1) == LOW && digitalRead(button2)== LOW) {
//         digitalWrite (led3, HIGH);
//         digitalWrite (led1, LOW);
//         digitalWrite (led2, LOW);
    
//     } else if (digitalRead(button1)== LOW) {
//         digitalWrite (led1, HIGH);
//         digitalWrite (led2, LOW);
//         digitalWrite (led3, LOW);
   
//     } else if (digitalRead(button2)== LOW) {
//         digitalWrite (led2, HIGH);
//         digitalWrite (led1, LOW);
//         digitalWrite (led3, LOW);
//     } else {
//         digitalWrite (led1, LOW);
//         digitalWrite (led2, LOW);
//         digitalWrite (led3, LOW);
//         }
// }