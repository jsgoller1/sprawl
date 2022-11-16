#include "InputEvent.hh"

#include "KeyboardPressEvent.hh"
#include "Logging.hh"
#include "MouseButtonPressEvent.hh"
#include "MouseMotionEvent.hh"
#include "SDLInputInterface.hh"

InputEvent::~InputEvent() = default;
InputEvent::InputEvent(const SDL_Event event) { this->sourceEvent = event; }

std::shared_ptr<InputEvent> InputEventFactory(const SDL_Event& event) {
  // NOTE: We actually do want to use a shared pointer here; we
  // will return a derived type of InputEvent.
  SDL_Keycode symbol;
  switch (event.type) {
    // TODO: For some reason, pressing a key my local keyboard causes both
    // SDL_TEXTINPUT (771) and SDL_KEYDOWN (768) on key press, but only
    // SDL_KEYUP (769) on release. Can just ignore the 771 for now.
    case SDL_KEYDOWN:
      symbol = event.key.keysym.sym;
      LOG_INFO_SYS(INPUT, "Key pressed: {0})", symbol);
      return std::shared_ptr<KeyboardPressEvent>(new KeyboardPressEvent(event));
    case SDL_MOUSEBUTTONDOWN:
      // TODO: This is just for debugging purposes so we can figure
      // out screen coordinates of where we clicked.
      LOG_INFO_SYS(INPUT, "Screen clicked at ({0},{1})", event.button.x, event.button.y);
      return std::shared_ptr<MouseButtonPressEvent>(new MouseButtonPressEvent(event));
    case SDL_MOUSEMOTION:
      LOG_INFO_SYS(INPUT, "Mouse moved to ({0},{1})", event.motion.x, event.motion.y);
      return std::shared_ptr<MouseMotionEvent>(new MouseMotionEvent(event));
    default:
      LOG_ERROR_SYS(INPUT, "Unhandleable input event: {}", event.type, event.button.y);
      return nullptr;
  }
}
