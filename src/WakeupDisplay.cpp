#include "Application.h"
#include "Arduino.h"

void setup() {
  Serial.begin(115200);
  delay(10);
  Application_Init();
}

void loop() {
  Application_MainLoop();
}
