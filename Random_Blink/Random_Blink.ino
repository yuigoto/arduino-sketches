#define LED_A 13
#define LED_B 10
#define LED_C 8

void setup() 
{
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  float test = random(1, 12);
  Serial.println("Hello!");
  if (test < 4) {
      digitalWrite(LED_A, HIGH);
      delay(100);
      digitalWrite(LED_A, LOW);
      delay(100);
  } else if (test < 8) {
      digitalWrite(LED_B, HIGH);
      delay(100);
      digitalWrite(LED_B, LOW);
      delay(100);
  } else {
      digitalWrite(LED_C, HIGH);
      delay(100);
      digitalWrite(LED_C, LOW);
      delay(100);
  }
}
