#pragma once

#include <Arduino.h>

// Line (Ls) + opponent IR (Os) stubs/drivers.
// Digital reads for now; swap to analog + thresholds when modules land.

namespace Sensors {

// Line sensors: true = seeing the white border (or dark dohyo — see ACTIVE).
// Opponent IR: true = object detected ahead.
struct Reading {
  bool ls1;
  bool ls2;
  bool ls3;
  bool ls4;
  bool os1;
  bool os2;
};

void begin();

// Fresh sample of all six channels.
Reading read();

// Convenience helpers from last read or a provided Reading.
bool anyEdge(const Reading& r);
bool frontEdge(const Reading& r);
bool rearEdge(const Reading& r);
bool opponentSeen(const Reading& r);

// Polarity (TBD): many Digikey line modules go HIGH on white/reflective.
// Set false if your modules are active-low.
static const bool LINE_ACTIVE_HIGH = true;
static const bool OPPONENT_ACTIVE_HIGH = true;

}  // namespace Sensors
