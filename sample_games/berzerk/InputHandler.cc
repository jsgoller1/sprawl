#include "InputHandler.hh"

bool InputHandler::gotSDLQuit() const { return this->_gotSDLQuit; }
bool InputHandler::escapePressed() const { return this->_escapePressed; }
bool InputHandler::upArrowPressed() const { return this->_upArrowPressed; }
bool InputHandler::downArrowPressed() const { return this->_downArrowPressed; }
bool InputHandler::leftArrowPressed() const { return this->_leftArrowPressed; }
bool InputHandler::rightArrowPressed() const { return this->_rightArrowPressed; }
bool InputHandler::lCtrlPressed() const { return this->_lCtrlPressed; }
bool InputHandler::bothHorizontalKeysPressed() const { return this->_leftArrowPressed && this->_rightArrowPressed; }
bool InputHandler::bothVerticalKeysPressed() const { return this->_upArrowPressed && this->_downArrowPressed; }

void InputHandler::getKeyboardInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      this->_gotSDLQuit = true;
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      keyboardEventHandler(event.type, event.key.keysym.sym);
    }
  }
}

void InputHandler::keyboardEventHandler(const Uint32 eventType, const SDL_Keycode keycode) {
  bool setting = (eventType == SDL_KEYDOWN) ? true : false;
  switch (keycode) {
    case SDLK_ESCAPE:
      this->_escapePressed = setting;
      break;
    case SDLK_UP:
      this->_upArrowPressed = setting;
      break;
    case SDLK_DOWN:
      this->_downArrowPressed = setting;
      break;
    case SDLK_LEFT:
      this->_leftArrowPressed = setting;
      break;
    case SDLK_RIGHT:
      this->_rightArrowPressed = setting;
      break;
    case SDLK_LCTRL:
      this->_lCtrlPressed = setting;
      break;
    default:
      break;
  }
}
