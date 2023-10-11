#include <SoftwareSerial.h>

enum SCALE_MODEL {
  CONFIANTEC,
  CONFIANTEC_OLD,
  GENOVA,
  JUNDIAI_T21,
  JUNDIAI_EPM,
  JUNDIAI_SP6000,
  JUNDIAI_TCA
};

const char* SCALE_NAME[] = {
  "CONFIANTEC",
  "CONFIANTEC OLD",
  "GENOVA",
  "JUNDIAI (T21)",
  "JUNDIAI (EPM)",
  "JUNDIAI (SP6000)",
  "JUNDIAI (TCA)"
};

const long BAUD_RATE[] = {
  300L, 600L, 750L, 1200L, 2400L, 4800L, 9600L, 19200L, 31250L, 38400L, 
  57600L, 74880L, 115200L, 230400L, 250000L, 460800L, 500000L
};

const int BAUD_RATE_LENGTH = 20;

const byte RX_PIN = 4;

const byte TX_PIN = 5;

SoftwareSerial SOFT_SERIAL = SoftwareSerial(RX_PIN, TX_PIN);

int CURRENT_BAUD = 6;

float CURRENT_WEIGHT = 0;

int STEP_WEIGHT = 100;

int WEIGHT_MIN = 0;

int WEIGHT_MAX = 12000;

SCALE_MODEL CURRENT_SCALE = CONFIANTEC;

bool UPWARDS = true;

void setup() {
  bootstrap();
  delay(2000);
}

void loop() {
  printValue();
  delay(300);
}

void bootstrap() {
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(BAUD_RATE[CURRENT_BAUD]);
  SOFT_SERIAL.begin(BAUD_RATE[CURRENT_BAUD]);

  Serial.flush();
  SOFT_SERIAL.flush();

  delay(100);

  Serial.println("CATU | Scale Emulator for Arduino | v0.0.1");
  Serial.println("Written by Fabio Y. Goto");
  Serial.println("------------------------------------------");
  Serial.println("DISCLAIMER:");
  Serial.println("Most scale models are still WIP.");
  Serial.println("Use it at your own risk.");
  Serial.println("------------------------------------------");
  Serial.print("Baud Rate: ");
  Serial.println(BAUD_RATE[CURRENT_BAUD]);
  Serial.print("Scale Model: ");
  Serial.println(SCALE_NAME[CURRENT_SCALE]);
  Serial.println("------------------------------------------");
  Serial.println("Starting emulated weighing...");
}

void printValue() {
  Serial.flush();
  SOFT_SERIAL.flush();

  if (UPWARDS) {
    CURRENT_WEIGHT += STEP_WEIGHT;

    if (CURRENT_WEIGHT >= WEIGHT_MAX) {
      UPWARDS = false;
    }
  } else {
    CURRENT_WEIGHT -= STEP_WEIGHT;

    if (CURRENT_WEIGHT <= WEIGHT_MIN) {
      CURRENT_WEIGHT = 0;
      UPWARDS = true;
    }
  }

  String weightToDisplay = "";

  switch (CURRENT_SCALE) {
    case CONFIANTEC:
      weightToDisplay = SCALE_MODEL_CONFIANTEC(CURRENT_WEIGHT);
      break;
    case CONFIANTEC_OLD:
      weightToDisplay = SCALE_MODEL_CONFIANTEC_OLD(CURRENT_WEIGHT);
      break;
    case JUNDIAI_T21:
      weightToDisplay = SCALE_MODEL_JUNDIAI_T21(CURRENT_WEIGHT);
      break;
    case JUNDIAI_EPM:
      weightToDisplay = SCALE_MODEL_JUNDIAI_EPM(CURRENT_WEIGHT);
      break;
    case JUNDIAI_SP6000:
      weightToDisplay = SCALE_MODEL_JUNDIAI_SP6000(CURRENT_WEIGHT);
      break;
    case JUNDIAI_TCA:
      weightToDisplay = SCALE_MODEL_JUNDIAI_TCA(CURRENT_WEIGHT);
      break;
    default:
      weightToDisplay = SCALE_MODEL_DEFAULT(CURRENT_WEIGHT);
      break;
  }

  SOFT_SERIAL.println(weightToDisplay);
  Serial.print(weightToDisplay);
}

int clamp(int value) {
  return max(min(value, BAUD_RATE_LENGTH - 1), 0);
}
