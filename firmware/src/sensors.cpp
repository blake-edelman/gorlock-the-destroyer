#include "sensors.h"
#include "pins.h"

namespace Sensors {

namespace {

bool sense(int pin, bool active_high) {
  const int level = digitalRead(pin);
  return active_high ? (level == HIGH) : (level == LOW);
}

}  // namespace

void begin() {
  pinMode(PIN_LS1, INPUT);
  pinMode(PIN_LS2, INPUT);
  pinMode(PIN_LS3, INPUT);
  pinMode(PIN_LS4, INPUT);
  pinMode(PIN_OS1, INPUT);
  pinMode(PIN_OS2, INPUT);
}

Reading read() {
  Reading r;
  r.ls1 = sense(PIN_LS1, LINE_ACTIVE_HIGH);
  r.ls2 = sense(PIN_LS2, LINE_ACTIVE_HIGH);
  r.ls3 = sense(PIN_LS3, LINE_ACTIVE_HIGH);
  r.ls4 = sense(PIN_LS4, LINE_ACTIVE_HIGH);
  r.os1 = sense(PIN_OS1, OPPONENT_ACTIVE_HIGH);
  r.os2 = sense(PIN_OS2, OPPONENT_ACTIVE_HIGH);
  return r;
}

bool anyEdge(const Reading& r) {
  return r.ls1 || r.ls2 || r.ls3 || r.ls4;
}

bool frontEdge(const Reading& r) {
  return r.ls1 || r.ls2;
}

bool rearEdge(const Reading& r) {
  return r.ls3 || r.ls4;
}

bool opponentSeen(const Reading& r) {
  return r.os1 || r.os2;
}

}  // namespace Sensors
