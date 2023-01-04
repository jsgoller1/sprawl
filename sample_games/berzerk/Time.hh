#pragma once

#include "SDL2/SDL.h"

// TODO: may want sleep() method

typedef Uint64 time_ms;

class Timer {
 public:
  Timer();
  time_ms tick();

 private:
  time_ms lastTick;
};
