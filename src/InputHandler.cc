#include "GameAction.hh"
#include "InputHandler.hh"
#include "Logger.hh"

GameAction InputHandler::getGameAction() {
  // TODO: For now, this forwarding method is a code smell;
  // eventually, we'll get inputs that won't cause game actions
  // i.e. (pausing the game, volume change, etc, which won't cause actions to
  // be given to World.update()), so we want to keep getting input and
  // getting game actions separate.
  return this->getInput()->getGameAction();
}

shared_ptr<InputEvent> InputHandler::getInput() {
  SDL_Event event;
  // TODO: Do we only want to try to get one event at a
  // time, or should we poll for all events and return a
  // collection?
  if (SDL_PollEvent(&event) == 0) {
    shared_ptr<NoEvent> action = shared_ptr<NoEvent>(new NoEvent());
    return action;
  }

  SDL_Keycode symbol;
  shared_ptr<InputEvent> inputEventSPtr;
  switch (event.type) {
    case SDL_QUIT:
      inputEventSPtr = shared_ptr<QuitEvent>(new QuitEvent());
      break;
    // TODO: For some reason, pressing a key my local keyboard causes both
    // SDL_TEXTINPUT (771) and SDL_KEYDOWN (768) on key press, but only
    // SDL_KEYUP (769) on release. Can just ignore the 771 for now.
    case SDL_KEYDOWN:
      symbol = event.key.keysym.sym;
      inputEventSPtr = shared_ptr<ButtonEvent>(new ButtonEvent(symbol));
      break;
    default:
      inputEventSPtr = shared_ptr<NoEvent>(new NoEvent());
      gLogger.log("Unhandleable input event: " + to_string(event.type));
      break;
  }
  return inputEventSPtr;
}

// TODO: Later on, we should refactor this to reference something like
// a vector<pair<SDL_Keycode,Command>> that will support both fast lookups
// of commands from actions, and also rebinding different commands to
// keys/buttons (probably can't use SDL_Keycode if we want to do mouse buttons)
GameAction ButtonEvent::getGameAction() {
  GameAction action;
  // TODO: Do we want to use SDLK or one of the other key representations?
  // Why do multiple exist?
  switch (this->value) {
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
GameAction QuitEvent::getGameAction() { return GameAction::QUIT; }
GameAction NoEvent::getGameAction() { return GameAction::IDLE; }
