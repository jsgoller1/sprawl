#pragma once

#include "GameAction.hh"
#include "Logging.hh"
#include "Types.hh"

class InputEvent {
 public:
  virtual GameAction getGameAction() = 0;
};

class ButtonDownEvent : public InputEvent {
  // Represents a key or mouse button being pressed

 public:
  ButtonDownEvent(const SDL_Keycode keycode) : keycode(keycode) {}
  GameAction getGameAction() override;

  // TODO: We will need other data from
  // SDL_EVENT later on;  when the key was
  // pressed, whether it was a repeat, etc.
  SDL_Keycode getKeycode() { return this->keycode; }

 private:
  SDL_Keycode keycode;
};

class ButtonUpEvent : public InputEvent {
  // Represents a key or mouse button being released

 public:
  ButtonUpEvent(const SDL_Keycode keycode) : keycode(keycode) {}
  GameAction getGameAction() override;

  // TODO: We will need other data from
  // SDL_EVENT later on;  when the key was
  // pressed, whether it was a repeat, etc.
  SDL_Keycode getKeycode() { return this->keycode; }

 private:
  SDL_Keycode keycode;
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
