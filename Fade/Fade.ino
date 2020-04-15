int led1 = 9; // Pino do led
int led2 = 10; // Pino do led
int led3 = 11; // Pino do led
int bri = 0; // Quantidade de brilho do led
int fad = 4; // Variação de degradê

void setup() 
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() 
{
  analogWrite(led1, bri);
  analogWrite(led2, bri);
  analogWrite(led3, bri);
  bri = bri + fad;
  if (bri == 0 || bri == 255) {
    fad = -fad;
  }
  delay(30);
}
