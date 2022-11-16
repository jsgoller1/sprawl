#include "KeyboardPressEvent.hh"

KeyboardPressEvent::KeyboardPressEvent(const SDL_Event event) : InputEvent(event) {}

Keycode KeyboardPressEvent::getKeycode() { return static_cast<Keycode>(this->sourceEvent.key.keysym.sym); }

// TODO: Later on, we should refactor this to reference something like
// a std::vector<pair<SDL_Keycode,Command>> that will support both fast lookups
// of commands from actions, and also rebinding different commands to
// keys/buttons (probably can't use SDL_Keycode if we want to do mouse buttons)
GameAction KeyboardPressEvent::getGameAction() const {
  GameAction action;
  // TODO: Do we want to use SDLK or one of the other key representations?
  // Why do multiple exist?
  switch (this->sourceEvent.key.keysym.sym) {
    case SDLK_ESCAPE:
      action = GameAction::QUIT;
      break;
    case SDLK_w:
      action = GameAction::MOVE_UP;
      break;
    case SDLK_s:
      action = GameAction::MOVE_DOWN;
      break;
    case SDLK_a:
      action = GameAction::MOVE_LEFT;
      break;
    case SDLK_d:
      action = GameAction::MOVE_RIGHT;
      break;
    case SDLK_LEFT:
      action = GameAction::SHOOT_LEFT;
      break;
    case SDLK_RIGHT:
      action = GameAction::SHOOT_RIGHT;
      break;
    case SDLK_DOWN:
      action = GameAction::SHOOT_DOWN;
      break;
    case SDLK_UP:
      action = GameAction::SHOOT_UP;
      break;
    default:
      action = GameAction::IDLE;
  }
  return action;
}
