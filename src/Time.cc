#include "Time.hh"

// Not sure if conversion from float to int / back will
// be dangerous, but in case it is would rather have
// helper methods than rely on users casting
time_ms_float to_float_time(const time_ms time) { return time_ms_float(time); }
time_ms to_int_time(const time_ms_float time) { return time_ms(time); }

Timer::Timer() { this->lastTick = SDL_GetTicks64(); }

time_ms Timer::tick() {
  time_ms current = SDL_GetTicks64();
  time_ms delta = current - this->lastTick;
  this->lastTick = current;
  return delta;
}

time_ms_float Timer::tickf() { return real(this->tick()); }
