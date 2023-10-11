#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

// ARDUINO PRO MICRO
// SCK = 3
// SDA = 2
// const byte RX_PIN = 8; // SOFT SERIAL RX1 
// const byte TX_PIN = 9; // SOFT SERIAL TX1

// ARDUINO NANO
// const byte RX_PIN = 8;
// const byte TX_PIN = 9;

// ARDUINO LEONARDO
// SCK = 3
// SDA = 2
const byte RX_PIN = 8; // A2
const byte TX_PIN = 9; // A3

SoftwareSerial SOFT_SERIAL = SoftwareSerial(RX_PIN, TX_PIN);
SoftwareSerial SOFT_SERIAL_2 = SoftwareSerial(10, 11);
 
Adafruit_SSD1306 display(128, 64);

String readString;

int BAUD_RATE = 9600;
 
void setup(){
  Wire.begin();

  Serial.begin(9600);
  Serial.flush();

  // Initialize OLED at the 0x3C I2C address
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(3);
  display.setCursor(0, 0);
  display.println("CERES");
  display.setTextSize(1);
  display.println("by Catu Sistemas");
  display.println("================");
  display.println("Initializing ...");
  display.display();

  SOFT_SERIAL.begin(BAUD_RATE);
  SOFT_SERIAL.flush();

  SOFT_SERIAL_2.begin(BAUD_RATE);
  SOFT_SERIAL_2.flush();
  
  delay(5000);
  display.clearDisplay();
}

void loop() {
  SOFT_SERIAL.listen();
    delay(10);

  while (SOFT_SERIAL.available()) {
    delay(10);

    if (SOFT_SERIAL.available() > 0) {
      char c = SOFT_SERIAL.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    } 
  }

  display.setCursor(0, 0);
  display.println("Awaiting input");
  display.println("---------------------");
  display.print("Baud rate: ");
  display.println(BAUD_RATE);
  display.println("---------------------");
  display.println("Last:");
  display.println("> 0x65");
  display.println(readString);
  display.display();
  delay(2);
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Awaiting input.");
  display.println("---------------------");
  display.print("Baud rate: ");
  display.println(BAUD_RATE);
  display.println("---------------------");
  display.println("Last:");
  display.println("> 0x65");
  display.println(readString);
  display.display();
  delay(2);
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Awaiting input..");
  display.println("---------------------");
  display.print("Baud rate: ");
  display.println(BAUD_RATE);
  display.println("---------------------");
  display.println("Last:");
  display.println("> 0x65");
  display.println(readString);
  display.display();
  delay(2);
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Awaiting input...");
  display.println("---------------------");
  display.print("Baud rate: ");
  display.println(BAUD_RATE);
  display.println("---------------------");
  display.println("Last:");
  display.println("> 0x65");
  display.println(readString);
  display.display();
  delay(2);
  display.clearDisplay();
  
  SOFT_SERIAL_2.listen();

  delay(100);

  SOFT_SERIAL_2.write("a");

  SOFT_SERIAL.listen();
    delay(10);
  
  readString = "";
}