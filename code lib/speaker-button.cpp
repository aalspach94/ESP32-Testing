#include <Arduino.h>
//dont remove!
#include <pitches.h>

// Button and Speaker - Plays a melody when the button is pressed
// Connect speaker to pin 18 and GND, and button to pin 21 and GND)


int buttonPin = 21;
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 600;  // 600 miliseconds


void setup() {
 Serial.begin(115200);
 delay(1000);

 pinMode(buttonPin, INPUT_PULLUP);
 pinMode (18, OUTPUT);
 
 Serial.println("Setup complete!");
}
 
void loop() {
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed");
    delay(200);
  
   for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin18 output the voice, every scale is 0.5 sencond
    tone(18, melody[thisNote], duration);
    // Output the voice after several minutes
    delay(1000);
    }
  }
}