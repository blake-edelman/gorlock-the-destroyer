#include <Arduino.h>

#include "pins.h"
#include "motors.h"
#include "sensors.h"
#include "debug.h"
#include "behavior.h"

void setup() {
  Debug::begin(115200);
  Motors::begin();
  Sensors::begin();
  Behavior::begin();

  Serial.println(F("pins (TBD defaults):"));
  Serial.print(F("  M_L pwm/in1/in2 "));
  Serial.print(PIN_MOTOR_L_PWM);
  Serial.print('/');
  Serial.print(PIN_MOTOR_L_IN1);
  Serial.print('/');
  Serial.println(PIN_MOTOR_L_IN2);
  Serial.print(F("  M_R pwm/in1/in2 "));
  Serial.print(PIN_MOTOR_R_PWM);
  Serial.print('/');
  Serial.print(PIN_MOTOR_R_IN1);
  Serial.print('/');
  Serial.println(PIN_MOTOR_R_IN2);
  Serial.print(F("  Ls "));
  Serial.print(PIN_LS1);
  Serial.print(',');
  Serial.print(PIN_LS2);
  Serial.print(',');
  Serial.print(PIN_LS3);
  Serial.print(',');
  Serial.println(PIN_LS4);
  Serial.print(F("  Os "));
  Serial.print(PIN_OS1);
  Serial.print(',');
  Serial.println(PIN_OS2);
}

void loop() {
  Behavior::tick();
  Debug::heartbeat(millis());
  delay(10);  // ~100 Hz
}
