#pragma once

// Gorlock pin map — named constants for early bring-up.
// All values below are REASONABLE ESP32 DEFAULTS / TBD until Cameron's
// wiring schematic lands. Marked (TBD) where Blake must confirm.

// -----------------------------------------------------------------------------
// Motor driver (assume dual H-bridge: TB6612 / DRV8833 / similar)
// Left = motor A (bot left when facing forward), Right = motor B.
// -----------------------------------------------------------------------------
static const int PIN_MOTOR_L_PWM = 25;  // TBD — PWMA / left enable
static const int PIN_MOTOR_L_IN1 = 26;  // TBD — AIN1
static const int PIN_MOTOR_L_IN2 = 27;  // TBD — AIN2
static const int PIN_MOTOR_R_PWM = 32;  // TBD — PWMB / right enable
static const int PIN_MOTOR_R_IN1 = 33;  // TBD — BIN1
static const int PIN_MOTOR_R_IN2 = 14;  // TBD — BIN2
// Optional STBY on TB6612 — tie high in hardware or drive this pin:
static const int PIN_MOTOR_STBY  = -1;  // TBD — set GPIO or leave -1 if hardwired

// -----------------------------------------------------------------------------
// Line / edge sensors Ls1–Ls4 (sketch: Ls1/Ls2 front edge, Ls3/Ls4 rear)
// Digital HIGH/LOW assumed; flip LINE_ACTIVE_HIGH in sensors.h if inverted.
// Prefer ADC-capable pins if modules are analog — swap later.
// -----------------------------------------------------------------------------
static const int PIN_LS1 = 34;  // TBD — front-left edge
static const int PIN_LS2 = 35;  // TBD — front-right edge
static const int PIN_LS3 = 36;  // TBD — rear-right (sketch Ls3)
static const int PIN_LS4 = 39;  // TBD — rear-left  (sketch Ls4)

// -----------------------------------------------------------------------------
// IR opponent sensors Os1–Os2 (sketch: front wedge face)
// -----------------------------------------------------------------------------
static const int PIN_OS1 = 4;   // TBD — front-right opponent
static const int PIN_OS2 = 16;  // TBD — front-left opponent

// Serial debug uses USB UART0 (GPIO1 TX / GPIO3 RX) — no remapping needed.
