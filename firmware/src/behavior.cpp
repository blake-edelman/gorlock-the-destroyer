#include "behavior.h"
#include "motors.h"
#include "sensors.h"
#include "debug.h"

namespace Behavior {

namespace {

enum class State : uint8_t {
  WaitStart,
  Seek,
  Charge,
  EdgeBackup,
  EdgeTurn,
};

State state = State::WaitStart;
unsigned long state_enter_ms = 0;
int turn_dir = 1;  // +1 right, -1 left
int last_left = 0;
int last_right = 0;

void enter(State next, unsigned long now_ms) {
  state = next;
  state_enter_ms = now_ms;
}

void applyDrive(int left, int right) {
  last_left = left;
  last_right = right;
  Motors::setBoth(left, right);
}

// Prefer turning away from the edge that tripped.
void chooseTurnFromEdge(const Sensors::Reading& r) {
  if (r.ls1 && !r.ls2) {
    turn_dir = 1;  // front-left → turn right
  } else if (r.ls2 && !r.ls1) {
    turn_dir = -1;
  } else if (r.ls4 && !r.ls3) {
    turn_dir = 1;  // rear-left → swing right
  } else if (r.ls3 && !r.ls4) {
    turn_dir = -1;
  } else {
    turn_dir = (turn_dir == 0) ? 1 : turn_dir;
  }
}

}  // namespace

void begin() {
  state = State::WaitStart;
  state_enter_ms = millis();
  Motors::stop();
  Serial.println(F("behavior: wait-start / seek / charge / edge"));
}

void tick() {
  const unsigned long now = millis();
  const Sensors::Reading r = Sensors::read();

  // Edge always wins — interrupt seek/charge.
  if (state != State::WaitStart &&
      state != State::EdgeBackup &&
      state != State::EdgeTurn &&
      Sensors::anyEdge(r)) {
    chooseTurnFromEdge(r);
    enter(State::EdgeBackup, now);
    Serial.print(F("edge! "));
    Debug::printSensors(r);
  }

  switch (state) {
    case State::WaitStart:
      Motors::stop();
      if (now - state_enter_ms >= START_DELAY_MS) {
        enter(State::Seek, now);
        Serial.println(F("state: seek"));
      }
      break;

    case State::Seek:
      if (Sensors::opponentSeen(r)) {
        enter(State::Charge, now);
        Serial.print(F("lock "));
        Debug::printSensors(r);
      } else {
        // Slow arc search.
        applyDrive(SEEK_SPEED, SEEK_SPEED * 70 / 100);
      }
      break;

    case State::Charge:
      if (!Sensors::opponentSeen(r)) {
        enter(State::Seek, now);
      } else if (r.os1 && !r.os2) {
        applyDrive(CHARGE_SPEED, CHARGE_SPEED * 60 / 100);  // veer right
      } else if (r.os2 && !r.os1) {
        applyDrive(CHARGE_SPEED * 60 / 100, CHARGE_SPEED);  // veer left
      } else {
        applyDrive(CHARGE_SPEED, CHARGE_SPEED);
      }
      break;

    case State::EdgeBackup:
      applyDrive(-BACK_SPEED, -BACK_SPEED);
      if (now - state_enter_ms >= EDGE_BACKUP_MS) {
        enter(State::EdgeTurn, now);
      }
      break;

    case State::EdgeTurn:
      if (turn_dir >= 0) {
        Motors::turnRight(TURN_SPEED);
        last_left = TURN_SPEED;
        last_right = -TURN_SPEED;
      } else {
        Motors::turnLeft(TURN_SPEED);
        last_left = -TURN_SPEED;
        last_right = TURN_SPEED;
      }
      if (now - state_enter_ms >= EDGE_TURN_MS) {
        enter(State::Seek, now);
        Serial.println(F("state: seek"));
      }
      break;
  }

  static unsigned long last_dbg = 0;
  if (now - last_dbg >= 500) {
    last_dbg = now;
    Debug::printSensors(r);
    Debug::printMotors(last_left, last_right);
  }
}

}  // namespace Behavior
