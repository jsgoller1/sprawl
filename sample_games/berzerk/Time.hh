#pragma once

#include "SDL2/SDL.h"

// TODO: may want sleep() method

typedef Uint64 time_ms;

class TimerProxy {
 public:
  TimerProxy(const time_ms* const currentTick, const time_ms* const previousTick);
  time_ms getCurrentTime() const;
  time_ms getTimeDelta() const;

 private:
  const time_ms* const _currentTick;
  const time_ms* const _previousTick;
};

class Timer {
 public:
  Timer();
  void tick();
  TimerProxy& getProxy();

 private:
  time_ms _currentTick;
  time_ms _previousTick;
  TimerProxy _proxy = TimerProxy(&this->_currentTick, &this->_previousTick);
};
