#pragma once

#include <memory>
#include <vector>

#include "KeyboardStateManager.hh"
#include "MouseStateManager.hh"
#include "SDL2/SDL.h"
#include "Singleton.hh"
#include "Types.hh"

// fwd decls
struct EventMessage;
class Vect2D;

class InputManager : public Singleton<InputManager> {
 public:
  bool getQuit();
  void gameLoopUpdate();

  bool getKey(int key);
  bool getKeyDown(int key);
  bool getKeyUp(int key);

  bool getMouseButton(Uint8 button);
  bool getMouseButtonDown(Uint8 button);
  bool getMouseButtonUp(Uint8 button);

  Vect2D getMousePosition();
  Vect2D getMousePositionDelta();

 private:
  friend Singleton<InputManager>;

  InputManager();
  InputManager(const InputManager&) = delete;
  InputManager& operator=(const InputManager&) = delete;

  std::unique_ptr<KeyboardStateManager> keyboardStateManager;
  std::unique_ptr<MouseStateManager> mouseStateManager;

  void updateInputs();
  void detectNewInputs();

  // SQL quit event occurred; this is usually due to pressing the X button on the window.
  bool _quit;
};
