#include "debug.h"

namespace Debug {

namespace {
unsigned long last_hb_ms = 0;
}

void begin(unsigned long baud) {
  Serial.begin(baud);
  delay(50);
  Serial.println();
  Serial.println(F("=== Gorlock The Destroyer firmware ==="));
  Serial.println(F("edge-avoid + seek sketch (bring-up)"));
}

void printSensors(const Sensors::Reading& r) {
  Serial.print(F("Ls["));
  Serial.print(r.ls1 ? '1' : '0');
  Serial.print(r.ls2 ? '1' : '0');
  Serial.print(r.ls3 ? '1' : '0');
  Serial.print(r.ls4 ? '1' : '0');
  Serial.print(F("] Os["));
  Serial.print(r.os1 ? '1' : '0');
  Serial.print(r.os2 ? '1' : '0');
  Serial.println(']');
}

void printMotors(int left_pct, int right_pct) {
  Serial.print(F("M L="));
  Serial.print(left_pct);
  Serial.print(F(" R="));
  Serial.println(right_pct);
}

void heartbeat(unsigned long now_ms) {
  if (now_ms - last_hb_ms < 1000) return;
  last_hb_ms = now_ms;
  Serial.println(F("hb"));
}

}  // namespace Debug
