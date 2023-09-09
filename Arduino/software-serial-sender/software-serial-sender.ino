/**
  Simple sketch to send data using both Serial and SoftwareSerial.

  SoftwareSerial sends data through 8 (RX) and 9 (TX) pins.
 */
#include <SoftwareSerial.h>

const int RX_PIN = 8;
const int TX_PIN = 9;

SoftwareSerial serialHandle(RX_PIN, TX_PIN);
int byteRead;

void setup() {
  serialHandle.begin(9600);
  Serial.begin(9600);
}

void loop() {
  serialHandle.println("Hello");
  Serial.println("Hello");

  delay(1000);
}
