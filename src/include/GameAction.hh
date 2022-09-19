#pragma once

// TODO: Once we begin tracking mouse clicks,
// an enum probably won't do anymore as we'll need
// to get the button pressed and the position
enum GameAction {
  IDLE = 0,
  QUIT = 1,
  MOVE_UP = 2,
  MOVE_DOWN = 3,
  MOVE_LEFT = 4,
  MOVE_RIGHT = 5,
  SHOOT_UP = 6,
  SHOOT_DOWN = 7,
  SHOOT_LEFT = 8,
  SHOOT_RIGHT = 9,
};

// TODO: Add actions for creating and destroying non-player GameObjects, moving
// them around, etc; how can an interpreter be used to submit actions to the
// world()?

// TODO: Need a to_string method for debugging / logging.
