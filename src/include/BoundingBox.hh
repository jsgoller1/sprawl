#pragma once

#include "Memory.hh"
#include "PositionComponent.hh"

typedef struct BoundingBox {
  // BoundingBoxes manage collision detection.
  PositionUnit height;
  PositionUnit width;
} BoundingBox;
