#include <Arduino.h>
//dont remove!

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
// #define or int variables here

const uint16_t kRecvPin = 21; // IR receiver pin 

#define GREEN_LED_PIN 19
#define RED_LED_PIN 18

IRrecv irrecv(kRecvPin);

decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    serialPrintUint64(results.value, HEX);
    if (results.value == 0xFF30CF) {
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
    } else if (results.value == 0xFF18E7) {
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
    } else {
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, LOW);
    }

  Serial.println("");
  irrecv.resume();  // Receive the next value
}
delay(100);
}