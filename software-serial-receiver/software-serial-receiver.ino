/**
  Simple sketch to receive data using both Serial and SoftwareSerial.

  SoftwareSerial uses pins 8 (RX) and 9 (TX).
 */
#include <SoftwareSerial.h>

const int RX_PIN = 8;
const int TX_PIN = 9;

SoftwareSerial serialHandle(RX_PIN, TX_PIN);
int byteRead;

void setup() {
  serialHandle.flush();
  Serial.flush();
  delay(500);

  serialHandle.begin(9600);
  Serial.begin(9600);
  delay(1000);

  Serial.println("<Arduino ready to receive data>");
  Serial.print("Using ports: ");
  Serial.print(RX_PIN);
  Serial.print(" (RX) and ");
  Serial.print(TX_PIN);
  Serial.println(" (TX)");
}

void loop() {
  if (serialHandle.available() > 0) {
    while (serialHandle.available() > 0) {
      byteRead = serialHandle.read();

      Serial.print("BYTE READ: ");
      Serial.print(byteRead);
      Serial.print(" | CHAR: ");
      Serial.println((char) byteRead);
    }
  }

  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      byteRead = Serial.read();

      Serial.print("BYTE READ: ");
      Serial.print(byteRead);
      Serial.print(" | CHAR: ");
      Serial.println(byteRead);
    }
  }

  delay(100);
}
