#pragma once

#include "InputEvent.hh"

class MouseButtonPressEvent : public InputEvent {
 public:
  MouseButtonPressEvent(const SDL_Event event);
  GameAction getGameAction() const override;
};
