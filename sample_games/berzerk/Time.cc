#include "Time.hh"

TimerProxy::TimerProxy(const time_ms* const currentTick, const time_ms* const previousTick)
    : _currentTick(currentTick), _previousTick(previousTick) {}

time_ms TimerProxy::getCurrentTime() const { return *this->_currentTick; }

time_ms TimerProxy::getTimeDelta() const { return *this->_currentTick - *this->_previousTick; }

Timer::Timer() {
  time_ms time = SDL_GetTicks64();
  this->_currentTick = time;
  this->_previousTick = time;
}

void Timer::tick() {
  this->_previousTick = this->_currentTick;
  this->_currentTick = SDL_GetTicks();
}

TimerProxy& Timer::getProxy() { return this->_proxy; }
