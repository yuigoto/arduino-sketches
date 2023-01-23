#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
Adafruit_SSD1306 display(128, 64);

int BAUD_RATE = 9600;
 
void setup(){
  Wire.begin();

  // Initialize OLED at the 0x3C I2C address
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("CERES");
  display.setTextSize(1);
  display.println("by Catu Sistemas");
  display.println("================");
  display.println("Initializing ...");
  display.display();
  
  delay(5000);
  display.clearDisplay();
}

void loop() {
  display.setCursor(0, 0);
  display.println("Awaiting input");
  display.println("---------------------");
  display.print("Baud rate: ");
  display.println(BAUD_RATE);
  display.println("---------------------");
  display.println("Last:");
  display.println("> 0x65");
  display.display();
  delay(200);
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Awaiting input.");
  display.println("---------------------");
  display.print("Baud rate: ");
  display.println(BAUD_RATE);
  display.println("---------------------");
  display.println("Last:");
  display.println("> 0x65");
  display.display();
  delay(200);
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Awaiting input..");
  display.println("---------------------");
  display.print("Baud rate: ");
  display.println(BAUD_RATE);
  display.println("---------------------");
  display.println("Last:");
  display.println("> 0x65");
  display.display();
  delay(200);
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Awaiting input...");
  display.println("---------------------");
  display.print("Baud rate: ");
  display.println(BAUD_RATE);
  display.println("---------------------");
  display.println("Last:");
  display.println("> 0x65");
  display.display();
  delay(200);
  display.clearDisplay();
}