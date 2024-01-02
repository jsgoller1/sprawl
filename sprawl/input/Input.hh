#include <SDL3/SDL.h>

#include "InputManager.hh"
#include "Math.hh"
/*
 * Facade for InputManager, used by game code to query input state.
 */
class Input {
 public:
  // TODO: It probably is inefficient to call InputManager::instance() every time we want to query
  // input state; however, I'd rather do this for now than store a possibly dead reference.
  bool getQuit() { return InputManager::instance().getQuit(); }
  void gameLoopUpdate() { InputManager::instance().gameLoopUpdate(); }

  bool getKey(int key) { return InputManager::instance().getKey(key); }
  bool getKeyDown(int key) { return InputManager::instance().getKeyDown(key); }
  bool getKeyUp(int key) { return InputManager::instance().getKeyUp(key); }

  bool getMouseButton(char button) { return InputManager::instance().getMouseButton(Uint8(button)); }
  bool getMouseButtonDown(char button) { return InputManager::instance().getMouseButtonDown(Uint8(button)); }
  bool getMouseButtonUp(char button) { return InputManager::instance().getMouseButtonUp(Uint8(button)); }

  Vect2D getMousePosition() { return InputManager::instance().getMousePosition(); }
  Vect2D getMousePositionDelta() { return InputManager::instance().getMousePositionDelta(); }
};
