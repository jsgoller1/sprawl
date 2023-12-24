#include "KeyboardStateManager.hh"

#include "Logging.hh"

void KeyboardStateManager::processEvent(SDL_Event event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      if (this->pressedKeys.find(event.key.keysym.sym) == this->pressedKeys.end() ||
          this->pressedKeys.at(event.key.keysym.sym) == InputPressState::NOT_PRESSED) {
        this->pressedKeys[event.key.keysym.sym] = InputPressState::PRESSED;
      }
      break;
    case SDL_KEYUP:
      this->pressedKeys[event.key.keysym.sym] = InputPressState::RELEASED;
      break;
    default:
      LOG_WARN("Unknown event type: {}", event.type);
      break;
  }
}

void KeyboardStateManager::updateInputs() {
  // A key changes from "pressed" to "held" after the first frame it's pressed,
  // and changes from "released" to "not pressed" after the first frame it's released.
  for (auto& [key, state] : this->pressedKeys) {
    if (state == InputPressState::PRESSED) {
      state = InputPressState::HELD;
    } else if (state == InputPressState::RELEASED) {
      state = InputPressState::NOT_PRESSED;
    }
  }
}

InputPressState KeyboardStateManager::getKeyState(SDL_Keycode key) const {
  if (this->pressedKeys.find(key) != this->pressedKeys.end()) {
    return this->pressedKeys.at(key);
  }
  return InputPressState::NOT_PRESSED;
}
