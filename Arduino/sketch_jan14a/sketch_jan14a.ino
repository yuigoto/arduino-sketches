#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *WIFI_SSID = "HELLOBALUGA";
const char *URL = "http://192.168.15.10:3000/api/hello";

WiFiClient client;
HTTPClient httpClient;

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  Serial.println("Connected");
}

void loop() {
  String data = "{\"message\": \"NodeMCU POST via WiFi over here\"}";

  httpClient.begin(client, URL);
  httpClient.addHeader("Content-Type", "application/json");
  httpClient.POST(data);
  String content = httpClient.getString();
  httpClient.end();

  Serial.println(content);
  delay(5000);
}
