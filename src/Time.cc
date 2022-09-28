#include "Time.hh"

Timer::Timer() { this->lastTick = SDL_GetTicks64(); }

time_ms Timer::tick() {
  time_ms current = SDL_GetTicks64();
  time_ms delta = current - this->lastTick;
  this->lastTick = current;
  return delta;
}

time_ms_float Timer::tickf() { return real(this->tick()); }
