/**
 * WIFI NETWORK SCANNER FOR ESP32
 * ====================================================================
 * Works mostly for the AI Thinker ESP32-CAM board.
 * 
 * Author: Fabio Y. Goto <lab@yuiti.dev>
 * Version: 0.0.1
 * Date: 2022/02/21
 */
#include <WiFi.h>

// ESP32 GPIO LED
#define LED_BUILTIN 2

void setup() {
  // Set serial comm to use 9600 baud rate
  Serial.begin(9600);

  // Set LED pin
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  wifiNetworkScan();
  delay(20000);
}

void wifiNetworkScan() {
  Serial.println("Searching for WiFi networks...");

  int count = WiFi.scanNetworks();
  int openNetworks = 0;
  String ssid = "";

  if (count > 0) {
    Serial.println(String(count) + " networks found.\n");
    delay(500);

    for (int i = 0; i < count; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(") ");

      if (WiFi.encryptionType(i) != WIFI_AUTH_OPEN) {
        Serial.println("*");
      } else {
        Serial.println();
        openNetworks++;
      }

      Serial.print("   -> Strength: ");
      Serial.println(WiFi.RSSI(i));
      Serial.print("   -> Channel: ");
      Serial.println(WiFi.channel(i));
      Serial.println();
    }
  } else {
    Serial.println("No networks found.");
  }
  
  return;
}
