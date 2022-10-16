#include "Direction.hh"

bool Direction::operator==(const Direction& dir) const {
  // Returns true if both vectors have same x and y components
  return eq(this->x, dir.x) && eq(this->y, dir.y);
}
