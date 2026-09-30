#pragma once

#include <Arduino.h>

// Differential-drive API for 2× N20 via dual H-bridge.
// Speed is signed percent: -100..+100 (negative = reverse).

namespace Motors {

void begin();

// Raw per-side control (PWM-friendly).
void setLeft(int speed_pct);
void setRight(int speed_pct);
void setBoth(int left_pct, int right_pct);

// Convenience maneuvers (use |speed_pct| for magnitude).
void forward(int speed_pct);
void backward(int speed_pct);
void turnLeft(int speed_pct);   // spin / pivot left
void turnRight(int speed_pct);  // spin / pivot right
void stop();

// Soft stop (coast) vs hard brake — driver-dependent.
void coast();
void brake();

}  // namespace Motors
