#pragma once

#include "Real.hh"
#include "Types.hh"
#include "Vect2D.hh"

/*
 * TODO: Not necessary quite yet, but I think it'd be better if Vect2D's methods
 * were virtual and Direction overrode them with constraints, although maybe
 * composition is preferred. I like the idea of being able to use a Direction
 * anywhere a Vect2D is used, but not that direction breaks whenever new methods
 * get added to Vect2D.
 */

class Direction {
 public:
  static Direction None() { return Direction(0.0, 0.0); }
  static Direction Up() { return Direction(0.0, 1.0); }
  static Direction Down() { return Direction(0.0, -1.0); }
  static Direction Left() { return Direction(-1.0, 0.0); }
  static Direction Right() { return Direction(1.0, 0.0); }
  static Direction LeftUp() { return Direction(-1.0, -1.0); }
  static Direction RightUp() { return Direction(1.0, -1.0); }
  static Direction LeftDown() { return Direction(-1.0, 1.0); }
  static Direction RightDown() { return Direction(1.0, 1.0); }
  Direction operator-(const Direction& other) const;
  Direction operator+(const Direction& other) const;
  bool operator==(const Direction& other) const;
  XCoord x() const { return this->_x; }
  YCoord y() const { return this->_y; }

 private:
  explicit Direction(XCoord x, XCoord y) : _x(x), _y(y) {}
  XCoord _x;
  YCoord _y;
};
