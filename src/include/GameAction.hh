#pragma once

// TODO: Once we begin tracking mouse clicks,
// an enum probably won't do anymore as we'll need
// to get the button pressed and the position
enum GameAction {
  IDLE,
  QUIT,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  STOP_MOVE_LEFT,
  MOVE_RIGHT,
  STOP_MOVE_RIGHT,
  SHOOT_UP,
  SHOOT_DOWN,
  SHOOT_LEFT,
  SHOOT_RIGHT,
};

// TODO: Add actions for creating and destroying non-player GameObjects, moving
// them around, etc; how can an interpreter be used to submit actions to the
// world()?

// TODO: Need a to_string method for debugging / logging.
