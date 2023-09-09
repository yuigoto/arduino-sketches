#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH    128
#define OLED_HEIGHT   64
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

void setup() {
	Serial.begin(9600); 
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Ceres");
  display.setTextSize(1);
  display.println("by Catu Sistemas");
  display.display();
  delay(5000);
}

void loop() {
  String demo = "";
  demo += random(12, 12480);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(demo + "kg");

  int which = random(0, 10);
  if (which < 5) {
    while (demo.length() < 6) {
      demo = " " + demo;
    }

    Serial.print("i" + demo + "kg\n\r");
  } else {
    while (demo.length() < 9) {
      demo = " " + demo;
    }

    Serial.print("*U\b\b" + demo + "kg \nÿ");
  }
  
  // Serial.print("i   248kg\n\r");
  // Serial.print("i" + demo + "kg\n\r");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 17);
  display.println("Status: OK");
  display.println("Model: Confiantec");
  display.println("Baud Rate: 9600");
  display.println("Data: 19/01/2021");
  display.println("Hora: 11:32");
  display.display();

  delay(1000);
}
