#pragma once

#include "Memory.hh"
#include "Real.hh"

/*
 * TODO: Not necessary quite yet, but I think it'd be better if Vect2D's methods
 * were virtual and Direction overrode them with constraints, although maybe
 * composition is preferred. I like the idea of being able to use a Direction
 * anywhere a Vect2D is used, but not that direction breaks whenever new methods
 * get added to Vect2D.
 */

class Direction {
 public:
  static shared_ptr<Direction> None() {
    return shared_ptr<Direction>(new Direction(0.0, 0.0));
  }
  static shared_ptr<Direction> Up() {
    return shared_ptr<Direction>(new Direction(0.0, -1.0));
  }
  static shared_ptr<Direction> Down() {
    return shared_ptr<Direction>(new Direction(0.0, 1.0));
  }
  static shared_ptr<Direction> Left() {
    return shared_ptr<Direction>(new Direction(-1.0, 0.0));
  }
  static shared_ptr<Direction> Right() {
    return shared_ptr<Direction>(new Direction(1.0, 0.0));
  }
  static shared_ptr<Direction> LeftUp() {
    return shared_ptr<Direction>(new Direction(-1.0, -1.0));
  }
  static shared_ptr<Direction> RightUp() {
    return shared_ptr<Direction>(new Direction(1.0, -1.0));
  }
  static shared_ptr<Direction> LeftDown() {
    return shared_ptr<Direction>(new Direction(-1.0, 1.0));
  }
  static shared_ptr<Direction> RightDown() {
    return shared_ptr<Direction>(new Direction(1.0, 1.0));
  }
  bool operator==(const Direction& other) const;
  XCoord getX() const { return this->x; }
  YCoord getY() const { return this->y; }

 private:
  explicit Direction(XCoord x, XCoord y) : x(x), y(y) {}
  XCoord x;
  YCoord y;
};
