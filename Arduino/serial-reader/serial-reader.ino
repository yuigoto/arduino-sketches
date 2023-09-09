#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

#include "config.h"

#define PIN_BUTTON_UP 6
#define PIN_BUTTON_DN 7
#define LED_PIN 13

#define RX_PIN 8
#define TX_PIN 9
 
Adafruit_SSD1306 display(128, 32);

SoftwareSerial serialHandle(8, 9);

int byteRead;

int UP_STATE = 0;
int DN_STATE = 0;
int LED_STATE = false;
bool MOVE = false;
bool CHANGED = false;

int CURRENT_BAUD = 6;
String LAST_RECEIVED = "";

void setup() {
  pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
  pinMode(PIN_BUTTON_DN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Wire.begin();

  // Initialize OLED at the 0x3C I2C address
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("SERIAL PORT READER");
  display.println("by Fabio Y. Goto");
  display.println("================");
  display.println("Initializing ...");
  display.display();

  serialStart();
  
  delay(5000);
  display.clearDisplay();
}

void loop() {
  buttonUpdate();

  if (CHANGED) {
    displayRefresh();
    serialStart();
    delay(100);
  } else {
    displayStatus();
    delay(250);
  }
}

void serialStart() {
  serialHandle.flush();
  Serial.flush();
  delay(100);

  serialHandle.begin(BAUD_RATE[CURRENT_BAUD]);
  Serial.begin(BAUD_RATE[CURRENT_BAUD]);
  delay(100);

  CHANGED = false;
}

void displayRefresh () {
  display.clearDisplay();
  
  display.setCursor(0, 0);
  display.println("CHANGING BAUD RATE");
  display.println("---------------------");
  display.display();
}

void displayStatus () {
  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("BAUD RATE: ");
  display.println(BAUD_RATE[CURRENT_BAUD]);
  display.println("---------------------"); 

  if (serialHandle.available() > 0) {
    String received = "";

    while (serialHandle.available() > 0) {
      byteRead = serialHandle.read();

      received += (char) byteRead;
    }

    LAST_RECEIVED = received;
  }

  display.println("Last message:");  
  display.print(">  ");
  display.println(LAST_RECEIVED);  
  display.println("");
  display.display();
}

void buttonUpdate() {
  if (!digitalRead(PIN_BUTTON_UP) && !UP_STATE) {
    UP_STATE = 1;
  } else if (digitalRead(PIN_BUTTON_UP) && UP_STATE > 0) {
    UP_STATE = 0;
  }

  if (!digitalRead(PIN_BUTTON_DN) && !UP_STATE) {
    DN_STATE = 1;
  } else if (digitalRead(PIN_BUTTON_DN) && DN_STATE > 0) {
    DN_STATE = 0;
  }

  LED_STATE = (UP_STATE - DN_STATE);

  if (MOVE && LED_STATE == 0) {
    MOVE = false;
  }

  if (!MOVE && LED_STATE != 0) {
    MOVE = true;

    if (LED_STATE > 0) {
      CURRENT_BAUD = clamp(CURRENT_BAUD + 1, BAUD_RATE_MIN, BAUD_RATE_MAX);
    } else if (LED_STATE < 0) {
      CURRENT_BAUD = clamp(CURRENT_BAUD - 1, BAUD_RATE_MIN, BAUD_RATE_MAX);
    }

    if (LED_STATE != 0) {
      CHANGED = true;
    }
  }
}
