#pragma once

#include "Math.hh"
#include "Memory.hh"
#include "PositionComponent.hh"
#include "Texture.hh"

class BoundingBox {
  /*
   * Implements basic bounding box collision testing using Rectangle. There are
   * some cases we need to be aware of when working with these
   * kinds of tests (see each collision function for descriptions of how to
   * handle them):
   * - A point either falls within a box or along its perimeter.
   * - A line can intersect, fall completely within, or be completely outside of
   * a box.
   * - Two boxes of equal size can not overlap at all, completely overlap, or
   * partly overlap. The same is true for testing a box against the trajectory
   * of another box of equal size.
   * - If box A is smaller than box B, it can not overlap or partly overlap, or
   * it can fall entirely inside box B. The same is true for testing a box
   * against the trajectory of another box of larger size.
   */
 public:
  BoundingBox(const Vect2D& center, const PositionUnit height, const PositionUnit width);
  BoundingBox(const BoundingBox& boundingBox);

  Rectangle box() const;

  bool checkCollision(const Vect2D& point) const;
  bool checkCollision(const Line& line) const;
  bool checkCollision(const BoundingBox& box) const;

  string toString() const;

 private:
  // Initialize dummy bounding box so we don't need default constructor
  // for bounding box.
  Rectangle _box = Rectangle(Vect2D::zero(), 1.0, 1.0);
};
