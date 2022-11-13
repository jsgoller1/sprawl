#include "Direction.hh"

bool Direction::operator==(const Direction& dir) const {
  // Returns true if both vectors have same x and y components
  return eq(this->_x, dir._x) && eq(this->_y, dir._y);
}

Direction Direction::operator+(const Direction& dir) const {
  // Returns true if both vectors have same x and y components
  return Direction(this->_x + dir._x, this->_y + dir._y);
}

Direction Direction::operator-(const Direction& dir) const {
  // Returns true if both vectors have same x and y components
  return Direction(this->_x - dir._x, this->_y - dir._y);
}
