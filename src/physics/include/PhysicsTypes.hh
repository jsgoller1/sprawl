#pragma once

#include "Types.hh"

enum CollisionAxis {
  // Collision occurs due to movement along both axes; it wouldn't occur without
  // movement along both axes; e.g. collision with another box sufficiently
  // up-and-rightward
  X_AND_Y = 0,
  // Collision occurs due to y-axis component of movement, irrespective of
  // x-axis movement; e.g. collision with the floor
  Y_ONLY = 1,
  // Collision occurs due to x-axis component of movement, irrespective of
  // y-axis movement; e.g. collision with a wall.
  X_ONLY = 2,
  // Collision occurs due to movements along either axis; performing either one
  // alone will cause it; e.g. collision with the perimeter of a box from inside
  // it
  X_OR_Y = 3
};

enum CollisionResolutionType {
  // Both the source and target objects respond to force; both will change
  // momentum but overall momentum will be preserved.
  ELASTIC,
  // The source object responds to force and the target does not; only the
  // source's momentum will change.
  INELASTIC,
  // The source object does not respond to force, but the target does; only the
  // target's momentum changes.
  PARTIAL_ELASTIC,
  // Neither the source nor the target respond to force; there is no momentum.
  PSEUDO
};
