#pragma once

#include "Math.hh"
#include "Memory.hh"
#include "PositionComp.hh"

typedef struct BoundingBoxParams {
  // Bounding boxes will usually remain constant in size, but need to be updated
  // every time the object they bound moves. As such, objects can keep track of
  // their dimensions and just construct them around their current position
  // whenever they need to test collisions.
  // TODO: Eventually, we will want to do bounds checking on boxes that are not
  // paralell / perpendictular to the coordinate axes. We can do this by storing
  // their rotation here, then figuring out how we need to rotate them when
  // doing collisions testing.
  PositionUnit height;
  PositionUnit width;

} BoundingBoxParams;

class BoundingBox {
  // BoundingBoxes manage collision detection.
 public:
  BoundingBox(const shared_ptr<BoundingBoxParams> params);
  BoundingBox(const shared_ptr<Vect2D> center, const PositionUnit height,
              const PositionUnit width);
  bool checkCollision(const shared_ptr<BoundingBox> box);

 private:
  shared_ptr<Vect2D> center;
  PositionUnit height;
  PositionUnit width;
};
