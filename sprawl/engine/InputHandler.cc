#include "InputHandler.hh"

InputEvent::~InputEvent() = default;
ButtonDownEvent::~ButtonDownEvent() = default;
ButtonUpEvent::~ButtonUpEvent() = default;
QuitEvent::~QuitEvent() = default;
NoEvent::~NoEvent() = default;

ButtonDownEvent::ButtonDownEvent(const SDL_Keycode keycode) : keycode(keycode) {}

SDL_Keycode ButtonDownEvent::getKeycode() { return this->keycode; }

GameAction InputHandler::getGameAction() {
  // TODO: For now, this forwarding method is a code smell;
  // eventually, we'll get inputs that won't cause game actions
  // i.e. (pausing the game, volume change, etc, which won't cause actions to
  // be given to World.update()), so we want to keep getting input and
  // getting game actions separate.
  return this->getInput()->getGameAction();
}

std::shared_ptr<InputEvent> InputHandler::getInput() {
  SDL_Event event;
  // TODO: Do we only want to try to get one event at a
  // time, or should we poll for all events and return a
  // collection?
  if (SDL_PollEvent(&event) == 0) {
    std::shared_ptr<NoEvent> action = std::shared_ptr<NoEvent>(new NoEvent());
    return action;
  }

  SDL_Keycode symbol;
  std::shared_ptr<InputEvent> inputEvent;
  switch (event.type) {
    case SDL_QUIT:
      inputEvent = std::shared_ptr<QuitEvent>(new QuitEvent());
      break;
    // TODO: For some reason, pressing a key my local keyboard causes both
    // SDL_TEXTINPUT (771) and SDL_KEYDOWN (768) on key press, but only
    // SDL_KEYUP (769) on release. Can just ignore the 771 for now.
    case SDL_KEYUP:
      symbol = event.key.keysym.sym;
      inputEvent = std::shared_ptr<ButtonUpEvent>(new ButtonUpEvent(symbol));
      break;
    case SDL_KEYDOWN:
      symbol = event.key.keysym.sym;
      inputEvent = std::shared_ptr<ButtonDownEvent>(new ButtonDownEvent(symbol));
      break;
    case SDL_MOUSEBUTTONDOWN:
      // TODO: This is just for debugging purposes so we can figure
      // out screen coordinates of where we clicked.
      LOG_INFO_SYS(INPUT, "Screen clicked at ({0},{1})", event.button.x, event.button.y);
      inputEvent = std::shared_ptr<NoEvent>(new NoEvent());
      break;
    default:
      inputEvent = std::shared_ptr<NoEvent>(new NoEvent());
      LOG_DEBUG_SYS(INPUT, "Unhandleable input event: {}", event.type, event.button.y);
      break;
  }
  return inputEvent;
}

// TODO: Later on, we should refactor this to reference something like
// a std::vector<pair<SDL_Keycode,Command>> that will support both fast lookups
// of commands from actions, and also rebinding different commands to
// keys/buttons (probably can't use SDL_Keycode if we want to do mouse buttons)
GameAction ButtonDownEvent::getGameAction() {
  GameAction action;
  // TODO: Do we want to use SDLK or one of the other key representations?
  // Why do multiple exist?
  switch (this->keycode) {
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

ButtonUpEvent::ButtonUpEvent(const SDL_Keycode keycode) : keycode(keycode) {}

SDL_Keycode ButtonUpEvent::getKeycode() { return this->keycode; }

GameAction ButtonUpEvent::getGameAction() {
  GameAction action;
  switch (this->keycode) {
    case SDLK_a:
      action = GameAction::STOP_MOVE_LEFT;
      break;
    case SDLK_d:
      action = GameAction::STOP_MOVE_RIGHT;
      break;
    default:
      action = GameAction::IDLE;
  }
  return action;
}

GameAction QuitEvent::getGameAction() { return GameAction::QUIT; }
GameAction NoEvent::getGameAction() { return GameAction::IDLE; }
