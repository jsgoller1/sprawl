#include "GameLoopInputEvents.hh"

GameLoopInputEvents::GameLoopInputEvents() {
  this->_shouldQuit = false;
  this->_events =
      std::unique_ptr<std::queue<std::shared_ptr<InputEvent>>>(new std::queue<std::shared_ptr<InputEvent>>());
}

bool GameLoopInputEvents::getShouldQuit() const { return this->_shouldQuit; }

void GameLoopInputEvents::setShouldQuit(const bool shouldQuit) { this->_shouldQuit = shouldQuit; }

bool GameLoopInputEvents::empty() const { return this->_events->empty(); }

void GameLoopInputEvents::insert(const std::shared_ptr<InputEvent> event) { this->_events->push(event); }

std::shared_ptr<InputEvent> GameLoopInputEvents::extract() {
  if (this->_events->empty()) {
    LOG_FATAL_SYS(INPUT, "No input events detected, prepare to die.");
  }
  std::shared_ptr<InputEvent> event = this->_events->front();
  this->_events->pop();
  return event;
}
