#include "Time.hh"

// Not sure if conversion from float to int / back will
// be dangerous, but in case it is would rather have
// helper methods than rely on users casting

time_ms to_miliseconds(const time_s time) { return time * 1000.0; }
time_s to_seconds(const time_ms time) { return time / 1000.0; }

Timer::Timer() { this->lastTick = SDL_GetTicks64(); }

time_ms Timer::tick() {
  time_ms current = SDL_GetTicks64();
  time_ms delta = current - this->lastTick;
  this->lastTick = current;
  return real(delta);
}
