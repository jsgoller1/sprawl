#pragma once

#include <map>

#include "SDL3/SDL.h"

/*
 * Manages button / key state (just pressed, held, released, not pressed)
 *
 * SDL has some odd behavior around detecting whether a key/button is pressed or not (appears to delegate this to the
 * driver, so it's not consistent across systems). On mine and others, this results in odd behavior when continuously
 * holding a key down, where the initial keystroke is detected, but then a delay occurs before more events are emitted.
 * To solve this, we keep a dict of pressed keys/buttons that gets updated on key/button down/up events, and then we
 * emit our own events based on that dict.
 */

enum class InputPressState { PRESSED, HELD, RELEASED, NOT_PRESSED };

class InputStateManager {
 public:
  virtual ~InputStateManager();
  virtual void processEvent(SDL_Event event) = 0;
  virtual void updateInputs() = 0;
};
