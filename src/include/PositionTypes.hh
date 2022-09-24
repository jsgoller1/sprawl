#pragma once
#include "Memory.hh"
#include "Types.hh"

// A Direction is a Vect2D whose x/y values
// can only be -1, 0, or 1 so it can function
// as a unit vector
enum DIRECTION_SCALAR { NEG_ONE = -1, ZERO = 0, ONE = 1 };
typedef struct Direction {
  const DIRECTION_SCALAR x;
  const DIRECTION_SCALAR y;
} Direction;

// TODO: See Effective CPP, Item 18.
// NOTE: In SDL, (0,0) is the top left of the screen,
// so smaller Y-coordinate values are closer to the top of the screen.
static const Direction NONE = Direction{.x = ZERO, .y = ZERO};
static const Direction UP = Direction{.x = ZERO, .y = NEG_ONE};
static const Direction DOWN = Direction{.x = ZERO, .y = ONE};
static const Direction LEFT = Direction{.x = NEG_ONE, .y = ZERO};
static const Direction RIGHT = Direction{.x = ONE, .y = ZERO};
static const Direction UP_LEFT = Direction{.x = NEG_ONE, .y = NEG_ONE};
static const Direction UP_RIGHT = Direction{.x = ONE, .y = NEG_ONE};
static const Direction DOWN_LEFT = Direction{.x = NEG_ONE, .y = ONE};
static const Direction DOWN_RIGHT = Direction{.x = ONE, .y = ONE};
