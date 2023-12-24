#include "MouseStateManager.hh"

MouseStateManager::MouseStateManager() = default;

void MouseStateManager::processEvent(SDL_Event event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    this->pressedMouseButtons[event.button.button] = InputPressState::PRESSED;
  } else if (event.type == SDL_MOUSEBUTTONUP) {
    this->pressedMouseButtons[event.button.button] = InputPressState::RELEASED;
  } else if (event.type == SDL_MOUSEMOTION) {
    this->mousePosition = Vect2D(XCoord(event.motion.x), YCoord(event.motion.y));
  }
}

void MouseStateManager::updateInputs() {
  // A button changes from "pressed" to "held" after the first frame it's pressed,
  // and changes from "released" to "not pressed" after the first frame it's released.
  for (auto& [button, state] : this->pressedMouseButtons) {
    if (state == InputPressState::PRESSED) {
      state = InputPressState::HELD;
    } else if (state == InputPressState::RELEASED) {
      state = InputPressState::NOT_PRESSED;
    }
  }
}

InputPressState MouseStateManager::getMouseButtonState(Uint8 button) const {
  if (this->pressedMouseButtons.find(button) != this->pressedMouseButtons.end()) {
    return this->pressedMouseButtons.at(button);
  } else {
    return InputPressState::NOT_PRESSED;
  }
}
Vect2D MouseStateManager::getMousePosition() const { return this->mousePosition; }
Vect2D MouseStateManager::getMousePositionDelta() const { return this->mousePosition - this->previousMousePosition; }
