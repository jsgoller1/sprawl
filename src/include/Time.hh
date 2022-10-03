#pragma once

#include "Types.hh"

// TODO: Need conversion methods and probably new struct-based types.
// TODO: do we want a seconds-based type as well?
// TODO: may want sleep() method

time_ms_float to_float_time(const time_ms time);
time_ms to_int_time(const time_ms_float time);

class Timer {
 public:
  Timer();
  time_ms tick();
  time_ms_float tickf();

 private:
  time_ms lastTick;
};
