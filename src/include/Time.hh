#include <SDL2/SDL.h>

#include "Math.hh"

// TODO: Need conversion methods and probably new struct-based types.
// TODO: do we want a seconds-based type as well?
// TODO: may want sleep() method

typedef unsigned long long time_ms;
typedef real time_ms_float;

// Not sure if conversion from float to int / back will
// be dangerous, but in case it is would rather have
// helper methods than rely on users casting
time_ms_float to_float_time(const time_ms time) { return time_ms_float(time); }
time_ms to_int_time(const time_ms_float time) { return time_ms(time); }

class Timer {
 public:
  Timer();
  time_ms tick();
  time_ms_float tickf();

 private:
  time_ms lastTick;
};
