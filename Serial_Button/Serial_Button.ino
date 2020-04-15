#define CHAVE 2
#define LED_A 13
#define MOTOR 11

boolean test = false;

void setup() 
{
  pinMode(LED_A, OUTPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(CHAVE, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(CHAVE)) {
    test = !test;
    Serial.println("Botão Pressionado");
  } else {
    Serial.println("Botão Não Pressionado");
  }
  if (test) {
    digitalWrite(LED_A, HIGH);
  } else {
    digitalWrite(LED_A, LOW);
  }
  delay(100);
}
