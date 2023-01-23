int value = 0;
bool upwards = true;

void setup() {
  // Define baud rate
  Serial.begin(9600);
}

void loop() {
  int maxWeight = 12000;
  int stepWeight = 100;
  String strValue = "";

  if (upwards) {
    value = value + stepWeight;

    if (value >= maxWeight) {
      upwards = false;
    }
  } else {
    value = value - stepWeight;

    if (value <= 0) {
      value = 0;
      upwards = true;
    }
  }

  int which = random(0, 10);
  strValue += value;

  if (which < 5) {
    while (strValue.length() < 6) {
      strValue = " " + strValue;
    }

    Serial.print("i" + strValue + "kg\n\r");
  } else {
    while (strValue.length() < 9) {
      strValue = " " + strValue;
    }

    Serial.print("*U\b\b" + strValue + "kg \nÿ");
  }
  
  delay(100);
}