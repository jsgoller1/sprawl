#pragma once

#include "Memory.hh"
#include "PositionComp.hh"

typedef struct BoundingBox {
  // BoundingBoxes manage collision detection.
  PositionUnit height;
  PositionUnit width;
} BoundingBox;

typedef shared_ptr<BoundingBox> BoundingBoxSPtr;
