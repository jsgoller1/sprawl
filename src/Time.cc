#include "Time.hh"

#include <SDL2/SDL.h>

// Not sure if conversion from float to int / back will
// be dangerous, but in case it is would rather have
// helper methods than rely on users casting

time_ms to_miliseconds(const time_s time) { return time * 1000.0; }
time_s to_seconds(const time_ms time) { return time / 1000.0; }

Timer::Timer() {
  // TODO: When we figure out units, do we really want to be casting this
  // UInt64 to a double?
  this->lastTick = real(SDL_GetTicks64());
}

time_ms Timer::tick() {
  time_ms current = real(SDL_GetTicks64());
  time_ms delta = current - this->lastTick;
  this->lastTick = current;
  return delta;
}
