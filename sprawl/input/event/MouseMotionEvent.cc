#include "MouseMotionEvent.hh"

MouseMotionEvent::MouseMotionEvent(const SDL_Event event) : InputEvent(event) {}

GameAction MouseMotionEvent::getGameAction() const { return GameAction::IDLE; }
