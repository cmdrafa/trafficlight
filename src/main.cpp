#include <Arduino.h>
#include <Timer.h>

#define LEDR 8
#define LEDY 7
#define LEDG 6
#define button 4

int seq = 0;
unsigned long previoustime = 0;
bool ledStatus = false;

void switchLights(uint8_t ledPin, unsigned long time, int seq);

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  if (digitalRead(button) == LOW) {
    if (seq == 0) {
      digitalWrite(LEDG, ledStatus);
    } else if (seq == 1) {
      digitalWrite(LEDY, ledStatus);
    }
    seq = 2;
  }

  switch (seq) {
  case 0:
    switchLights(LEDG, 9000, 1);
    break;
  case 1:
    switchLights(LEDY, 2000, 2);
    break;
  case 2:
    switchLights(LEDR, 5000, 0);
    break;
  }
}

void switchLights(uint8_t ledPin, unsigned long time, int next) {
  unsigned long Timer = millis();
  digitalWrite(ledPin, !ledStatus);
  if (Timer - previoustime >= time) {
    previoustime = Timer;

    digitalWrite(ledPin, ledStatus);
    seq = next;
  }
}
