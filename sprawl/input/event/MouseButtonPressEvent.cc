#include "MouseButtonPressEvent.hh"

MouseButtonPressEvent::MouseButtonPressEvent(const SDL_Event event) : InputEvent(event) {}

GameAction MouseButtonPressEvent::getGameAction() const { return GameAction::IDLE; }
