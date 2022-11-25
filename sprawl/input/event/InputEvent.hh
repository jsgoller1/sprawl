#pragma once

#include "SDL2/SDL.h"

#include <memory>

#include "SDLInputInterface.hh"
// TODO: We actually don't want GameAction here; we will have a separate class for keybindings that translate
// InputEvents to GameActions
// Actually we might; since input key binding should be done in the input system, we might want to have each input event
// know what kind of game action it should cause, assuming it's not meant for the UI.
#include "GameAction.hh"

class InputEvent {
 public:
  virtual ~InputEvent();
  virtual GameAction getGameAction() const = 0;

 protected:
  InputEvent(const SDL_Event event);
  SDL_Event sourceEvent;
};

std::shared_ptr<InputEvent> InputEventFactory(const SDL_Event& event);
