#pragma once

#include "Memory.hh"

class BoundingBox {
  // BoundingBoxes manage collision detection. SDL implements several functions
  // we can use for this, but they require using SDL-specific classes that we'd
  // have to expose, so we may want to use a Strategy or Factory to allow that
  // if we're using SDL-based bounding boxes
};

typedef shared_ptr<BoundingBox> BoundingBoxSPtr;
