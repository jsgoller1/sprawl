#pragma once
#include <SDL2/SDL.h>

#include "GameAction.hh"
#include "Logger.hh"
#include "Memory.hh"
#include "Types.hh"

class InputEvent {
 public:
  virtual GameAction getGameAction() = 0;
};

class ButtonDownEvent : public InputEvent {
  // Represents a key or mouse button being pressed

 public:
  ButtonDownEvent(const SDL_Keycode value) : value(value) {}
  GameAction getGameAction() override;

  // TODO: We will need other data from
  // SDL_EVENT later on;  when the key was
  // pressed, whether it was a repeat, etc.
  SDL_Keycode value;
};

class ButtonUpEvent : public InputEvent {
  // Represents a key or mouse button being released

 public:
  ButtonUpEvent(const SDL_Keycode value) : value(value) {}
  GameAction getGameAction() override;

  // TODO: We will need other data from
  // SDL_EVENT later on;  when the key was
  // pressed, whether it was a repeat, etc.
  SDL_Keycode value;
};

class QuitEvent : public InputEvent {
 public:
  GameAction getGameAction() override;
};

class NoEvent : public InputEvent {
 public:
  GameAction getGameAction() override;
};

class InputHandler {
 public:
  GameAction getGameAction();
  shared_ptr<InputEvent> getInput();
};
