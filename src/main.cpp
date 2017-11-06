#include <Arduino.h>
#include <stdlib.h>

#define LEDR 8
#define LEDY 7
#define LEDG 6
#define button 4
#define remoteControl 3

int state = 0;
bool maintCheck = true;
unsigned long previoustime = 0;
bool ledStatus = false;

void switchLights(uint8_t ledPin, unsigned long time, int seq);
void maintenance();

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(button, INPUT);
  pinMode(remoteControl, INPUT);
}

void loop() {
  if (digitalRead(button) == LOW) {
    digitalWrite(LEDG, ledStatus);
    digitalWrite(LEDY, ledStatus);
    state = 1;
  }

  if (digitalRead(remoteControl) == LOW) {
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDR, LOW);
    state = 3;
  }

  switch (state) {
  case 0:
    switchLights(LEDG, 9000, 1);
    break;
  case 1:
    switchLights(LEDY, 1000, 2);
    break;
  case 2:
    switchLights(LEDR, 5000, 0);
    break;
  case 3:
    maintenance();
  }
}

void switchLights(uint8_t ledPin, unsigned long time, int next) {
  unsigned long Timer = millis();
  digitalWrite(ledPin, !ledStatus);
  if (Timer - previoustime >= time) {
    previoustime = Timer;

    digitalWrite(ledPin, ledStatus);
    state = next;
  }
}

void maintenance() {
  unsigned long Timer = millis();
  if (Timer - previoustime >= 1000) {
    ledStatus = !ledStatus;
    digitalWrite(LEDY, ledStatus);
    previoustime = millis();
  }
  if (digitalRead(remoteControl) == LOW) {
    state = 0;
    return;
  }
}
