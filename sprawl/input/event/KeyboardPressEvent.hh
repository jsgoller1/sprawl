#pragma once

#include <SDL2/SDL.h>

#include "GameAction.hh"
#include "InputEvent.hh"
#include "Types.hh"

class KeyboardPressEvent : public InputEvent {
  // Represents a key or mouse button being pressed

 public:
  KeyboardPressEvent(const SDL_Event event);
  GameAction getGameAction() const override;

  // TODO: We will need other data from
  // SDL_EVENT later on;  when the key was
  // pressed, whether it was a repeat, etc.
  SDL_Keycode getKeycode();
};
