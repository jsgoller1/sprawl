#include "InputManager.hh"

#include "EventBusPublisher.hh"
#include "EventMessage.hh"
#include "InputStateManager.hh"
#include "Logging.hh"
#include "Math.hh"

InputManager::InputManager() {
  this->keyboardStateManager = std::make_unique<KeyboardStateManager>();
  this->mouseStateManager = std::make_unique<MouseStateManager>();
  this->_quit = false;
}

void InputManager::gameLoopUpdate() {
  this->updateInputs();
  this->detectNewInputs();
}

void InputManager::updateInputs() {
  this->keyboardStateManager->updateInputs();
  this->mouseStateManager->updateInputs();
}

/*
 * Detects input from SDL and enqueues messages to be sent to the EventBus.
 */
void InputManager::detectNewInputs() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        this->_quit = true;
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        this->keyboardStateManager->processEvent(event);
        break;
      case SDL_MOUSEMOTION:
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        this->mouseStateManager->processEvent(event);
      default:
        break;
    }
  }
}

bool InputManager::getQuit() { return this->_quit; }
bool InputManager::getKey(int key) {
  bool held = this->keyboardStateManager->getKeyState(key) == InputPressState::HELD;
  bool pressed = this->keyboardStateManager->getKeyState(key) == InputPressState::PRESSED;
  return held || pressed;
}
bool InputManager::getKeyDown(int key) {
  return this->keyboardStateManager->getKeyState(key) == InputPressState::PRESSED;
}
bool InputManager::getKeyUp(int key) {
  return this->keyboardStateManager->getKeyState(key) == InputPressState::RELEASED;
}

bool InputManager::getMouseButton(Uint8 button) {
  bool held = this->mouseStateManager->getMouseButtonState(button) == InputPressState::HELD;
  bool pressed = this->mouseStateManager->getMouseButtonState(button) == InputPressState::PRESSED;
  return held || pressed;
}
bool InputManager::getMouseButtonDown(Uint8 button) {
  return this->mouseStateManager->getMouseButtonState(button) == InputPressState::HELD;
}
bool InputManager::getMouseButtonUp(Uint8 button) {
  return this->mouseStateManager->getMouseButtonState(button) == InputPressState::RELEASED;
}

Vect2D InputManager::getMousePosition() { return this->mouseStateManager->getMousePosition(); }
Vect2D InputManager::getMousePositionDelta() { return this->mouseStateManager->getMousePositionDelta(); }
