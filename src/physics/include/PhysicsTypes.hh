#pragma once

#include "Types.hh"

enum CollisionAxis { X_ONLY, Y_ONLY, X_AND_Y };

enum CollisionType {
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
