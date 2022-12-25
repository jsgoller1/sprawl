#include "InputHandler.hh"

#include <SDL2/SDL.h>

bool InputHandler::gotSDLQuit() const { return this->_gotSDLQuit; }
bool InputHandler::escapePressed() const { return this->_escapePressed; }

void InputHandler::getKeyboardInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      this->_gotSDLQuit = true;
    } else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case '\x1B':
          this->_escapePressed = true;
          break;
        default:
          break;
      }
    }
  }
}
