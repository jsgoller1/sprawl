#pragma once

#include "InputStateManager.hh"

class KeyboardStateManager : public InputStateManager {
 public:
  void processEvent(SDL_Event event) override;
  void updateInputs() override;

  InputPressState getKeyState(SDL_Keycode key) const;

 private:
  std::map<SDL_Keycode, InputPressState> pressedKeys;
};
