#include "motors.h"
#include "pins.h"

namespace Motors {

namespace {

constexpr int kPwmFreqHz = 20000;
constexpr int kPwmBits = 8;  // 0–255 duty
constexpr int kChLeft = 0;
constexpr int kChRight = 1;

int clampPct(int pct) {
  if (pct > 100) return 100;
  if (pct < -100) return -100;
  return pct;
}

int pctToDuty(int abs_pct) {
  return (abs_pct * 255) / 100;
}

void driveSide(int in1, int in2, int pwm_ch, int speed_pct) {
  speed_pct = clampPct(speed_pct);
  if (speed_pct > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    ledcWrite(pwm_ch, pctToDuty(speed_pct));
  } else if (speed_pct < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    ledcWrite(pwm_ch, pctToDuty(-speed_pct));
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    ledcWrite(pwm_ch, 0);
  }
}

}  // namespace

void begin() {
  pinMode(PIN_MOTOR_L_IN1, OUTPUT);
  pinMode(PIN_MOTOR_L_IN2, OUTPUT);
  pinMode(PIN_MOTOR_R_IN1, OUTPUT);
  pinMode(PIN_MOTOR_R_IN2, OUTPUT);

  ledcSetup(kChLeft, kPwmFreqHz, kPwmBits);
  ledcSetup(kChRight, kPwmFreqHz, kPwmBits);
  ledcAttachPin(PIN_MOTOR_L_PWM, kChLeft);
  ledcAttachPin(PIN_MOTOR_R_PWM, kChRight);

  if (PIN_MOTOR_STBY >= 0) {
    pinMode(PIN_MOTOR_STBY, OUTPUT);
    digitalWrite(PIN_MOTOR_STBY, HIGH);
  }

  stop();
}

void setLeft(int speed_pct) {
  driveSide(PIN_MOTOR_L_IN1, PIN_MOTOR_L_IN2, kChLeft, speed_pct);
}

void setRight(int speed_pct) {
  driveSide(PIN_MOTOR_R_IN1, PIN_MOTOR_R_IN2, kChRight, speed_pct);
}

void setBoth(int left_pct, int right_pct) {
  setLeft(left_pct);
  setRight(right_pct);
}

void forward(int speed_pct) {
  const int s = abs(clampPct(speed_pct));
  setBoth(s, s);
}

void backward(int speed_pct) {
  const int s = abs(clampPct(speed_pct));
  setBoth(-s, -s);
}

void turnLeft(int speed_pct) {
  const int s = abs(clampPct(speed_pct));
  setBoth(-s, s);
}

void turnRight(int speed_pct) {
  const int s = abs(clampPct(speed_pct));
  setBoth(s, -s);
}

void stop() {
  setBoth(0, 0);
}

void coast() {
  // Same as stop for this driver API; PWM=0 + INs low = coast on many bridges.
  stop();
}

void brake() {
  digitalWrite(PIN_MOTOR_L_IN1, HIGH);
  digitalWrite(PIN_MOTOR_L_IN2, HIGH);
  digitalWrite(PIN_MOTOR_R_IN1, HIGH);
  digitalWrite(PIN_MOTOR_R_IN2, HIGH);
  ledcWrite(kChLeft, 255);
  ledcWrite(kChRight, 255);
}

}  // namespace Motors
