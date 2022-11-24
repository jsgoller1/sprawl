#pragma once

#include "InputEvent.hh"

class MouseMotionEvent : public InputEvent {
 public:
  MouseMotionEvent(const SDL_Event event);
  GameAction getGameAction() const override;
};
