#include "SDLInputInterface.hh"

using std::map;
using std::queue;
using std::shared_ptr;

SDLInputInterface::SDLInputInterface() {
  this->_recievedQuitEvent = false;
  this->_pressedKeys =
      shared_ptr<map<SDL_Keycode, shared_ptr<SDL_Event>>>(new map<SDL_Keycode, shared_ptr<SDL_Event>>());
  this->_pressedMouseButtons = shared_ptr<map<Uint8, shared_ptr<SDL_Event>>>(new map<Uint8, shared_ptr<SDL_Event>>());
  this->_mouseMotionEvents = shared_ptr<queue<shared_ptr<SDL_Event>>>(new queue<shared_ptr<SDL_Event>>());
}

bool SDLInputInterface::recievedQuitEvent() const { return this->_recievedQuitEvent; }

shared_ptr<queue<shared_ptr<SDL_Event>>> SDLInputInterface::getKeydownEvents() {
  shared_ptr<queue<shared_ptr<SDL_Event>>> keydownEvents =
      shared_ptr<queue<shared_ptr<SDL_Event>>>(new queue<shared_ptr<SDL_Event>>());
  for (auto eventPair : *this->_pressedKeys) {
    keydownEvents->push(eventPair.second);
  }
  return keydownEvents;
}
shared_ptr<queue<shared_ptr<SDL_Event>>> SDLInputInterface::getMouseButtonDownEvents() {
  shared_ptr<queue<shared_ptr<SDL_Event>>> mouseButtonDownEvents =
      shared_ptr<queue<shared_ptr<SDL_Event>>>(new queue<shared_ptr<SDL_Event>>());
  for (auto eventPair : *this->_pressedMouseButtons) {
    mouseButtonDownEvents->push(eventPair.second);
  }
  return mouseButtonDownEvents;
}
shared_ptr<queue<shared_ptr<SDL_Event>>> SDLInputInterface::getMouseMotionEvents() { return this->_mouseMotionEvents; }

void SDLInputInterface::detectInput() {
  SDL_Event rawEvent;
  while (SDL_PollEvent(&rawEvent) != 0) {
    shared_ptr<SDL_Event> event = shared_ptr<SDL_Event>(new SDL_Event(rawEvent));
    switch (event->type) {
      case SDL_QUIT:
        this->_recievedQuitEvent = true;
        break;
      case SDL_KEYDOWN:
        this->handler_SDL_KEYDOWN(event);
        break;
      case SDL_KEYUP:
        this->handler_SDL_KEYUP(event);
        break;
      case SDL_MOUSEBUTTONDOWN:
        this->handler_SDL_MOUSEBUTTONDOWN(event);
        break;
      case SDL_MOUSEBUTTONUP:
        this->handler_SDL_MOUSEBUTTONUP(event);
        break;
      case SDL_MOUSEMOTION:
        this->handler_SDL_MOUSEMOTION(event);
        break;
    }
  }
}

void SDLInputInterface::handler_SDL_KEYDOWN(const shared_ptr<SDL_Event> event) {
  this->_pressedKeys->operator[](event->key.keysym.sym) = event;
}

void SDLInputInterface::handler_SDL_KEYUP(const shared_ptr<SDL_Event> event) {
  if (this->_pressedKeys->find(event->key.keysym.sym) == this->_pressedKeys->end()) {
    LOG_WARN_SYS(LoggingSubsystem::INPUT, "Detected an SDL_KEYUP event for a key that was not pressed: {0}",
                 event->key.keysym.sym);
    return;
  }
  this->_pressedKeys->erase(event->key.keysym.sym);
}

void SDLInputInterface::handler_SDL_MOUSEBUTTONDOWN(const shared_ptr<SDL_Event> event) {
  this->_pressedKeys->operator[](event->button.button) = event;
}

void SDLInputInterface::handler_SDL_MOUSEBUTTONUP(const shared_ptr<SDL_Event> event) {
  if (this->_pressedKeys->find(event->button.button) == this->_pressedKeys->end()) {
    LOG_WARN_SYS(LoggingSubsystem::INPUT,
                 "Detected an handler_SDL_MOUSEBUTTONUP event for a button that was not pressed: {0}",
                 event->button.button);
    return;
  }
  this->_pressedKeys->erase(event->button.button);
}

void SDLInputInterface::handler_SDL_MOUSEMOTION(const shared_ptr<SDL_Event> event) {
  this->_mouseMotionEvents->push(event);
}
