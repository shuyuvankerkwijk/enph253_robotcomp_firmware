#include <Arduino.h>
#include "ws.h"
#include "crane.h"
#include "bluepill_uart.h"
#include "esp2_uart.h"
#include "vacuum.h"
#include "pinout.h"
#include "driver/ledc.h"

bool run = true;
int moveR = 1; // starts at negative position, can never be positive
int moveY = 0;
int moveZ = -1; // starts at 0 position, so can never be -1

void setup() {
  // These pins default high, so start by setting them low
  // Serial.begin(115200);
  pinMode(14, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(39, OUTPUT);
  digitalWrite(14, LOW);
  digitalWrite(20, LOW);
  digitalWrite(0, LOW);
  digitalWrite(39, LOW); 

  bluepillUartSetup();
  esp2UartSetup();
  wsSetup();
  // vacuumSetupF();
  // craneSetupF();
  vacuumSetupB();
  craneSetupB();
}

void loop() {
  if (moveR != 1) {
    wsSend("Moving R " + String(moveR));
    while (moveR != 1) {
      bool doneR = craneMoveRB(moveR);
      if (doneR) {
        moveR = 1;
        wsSend("Done moving R, set moveR to 1");
      }
    }
  } else if (moveZ != 0) {
    wsSend("Moving Z " + String(moveZ));
    while (moveZ != 0) {
      bool doneZ = craneMoveZB(moveZ);
      if (doneZ) {
        moveZ = 0;
        wsSend("Done moving Z, set moveZ to 0");
      }
    }
  } else if (moveY != 0) {
    wsSend("Moving Y " + String(moveY));
    while (moveY != 0) {
      bool doneY = craneMoveYB(moveY);
      if (doneY) {
        moveY = 0;
        wsSend("Done moving Y, set moveY to 0");
      }
    }
  }
}