#include <Arduino.h>

#include <Arduino.h>
#define LED_PIN 2
void setup() {
  Serial.begin(115200); pinMode(LED_PIN, OUTPUT); Serial.println("ESP32 Blink Test Started");
}
void loop() {
 digitalWrite(LED_PIN, HIGH);
 delay(1000);
 digitalWrite(LED_PIN, LOW);
 delay(1000);}