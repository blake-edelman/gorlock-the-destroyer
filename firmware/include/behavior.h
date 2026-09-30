#pragma once

#include <Arduino.h>

// Minimal sumo sketch: edge avoid + opponent seek.
// Tunables live here so pin/hardware changes stay out of the FSM.

namespace Behavior {

void begin();
void tick();  // call from loop() at ~50–100 Hz

// Speeds / timings (TBD — tune on mat).
static const int SEEK_SPEED      = 55;
static const int CHARGE_SPEED    = 80;
static const int TURN_SPEED      = 60;
static const int BACK_SPEED      = 50;
static const unsigned long EDGE_BACKUP_MS = 180;
static const unsigned long EDGE_TURN_MS   = 220;
static const unsigned long START_DELAY_MS = 0;  // set 3000–5000 if rules require

}  // namespace Behavior
