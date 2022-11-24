#pragma once

#include <string>

// TODO: Once we begin tracking mouse clicks,
// an enum probably won't do anymore as we'll need
// to get the button pressed and the position

// TODO: Add actions for creating and destroying non-player GameObjects, moving
// them around, etc; how can an interpreter be used to submit actions to the
// world()?

// TODO: Need a to_string method for debugging / logging.

/*
 * A GameAction represents a behavior the user has requested from the engine via input from the mouse, keyboard, etc. In
 * most cases, it was preceded by an InputEvent.
 */
enum GameAction {
  IDLE,
  QUIT,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  SHOOT_UP,
  SHOOT_DOWN,
  SHOOT_LEFT,
  SHOOT_RIGHT,
};

std::string toString(const GameAction& action);
