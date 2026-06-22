// code credit - https://heqingele.com/blog/rc522-datasheet-arduino-interface-2025/
#include <Arduino.h>

#include <SPI.h>
#include <MFRC522.h>

// SDA(SS) on 21, SCK on 18, MOSI on 23, MISO on 19, RST on 5, then 3v3+GND.  
#define RST_PIN  5
#define SS_PIN  21

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Place your RFID tag near the reader...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Tag UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  rfid.PICC_HaltA();
}