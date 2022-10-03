#pragma once

#include "Types.hh"

// TODO: Need conversion methods and probably new struct-based types.
// TODO: do we want a seconds-based type as well?
// TODO: may want sleep() method

time_ms to_miliseconds(const time_s time);
time_s to_seconds(const time_ms time);

class Timer {
 public:
  Timer();
  time_ms tick();

 private:
  time_ms lastTick;
};
