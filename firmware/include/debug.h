#pragma once

#include <Arduino.h>
#include "sensors.h"

namespace Debug {

void begin(unsigned long baud = 115200);
void printSensors(const Sensors::Reading& r);
void printMotors(int left_pct, int right_pct);
void heartbeat(unsigned long now_ms);

}  // namespace Debug
