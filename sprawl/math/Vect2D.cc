#include "Vect2D.hh"

#include "fmt/format.h"

/*
 * This code was adapted from cyclone-physics by Ian Millington.
 * cyclone-physics is released under the MIT license, and is copyright (c)
 * 2003-2009 Ian Millington.
 * cyclone-physics:
 * https://github.com/idmillington/cyclone-physics/
 * MIT License:
 * https://raw.githubusercontent.com/idmillington/cyclone-physics/master/LICENSE
 */

Vect2D::Vect2D(XCoord x, YCoord y) {
  this->_x = x;
  this->_y = y;
}
// Vect2D::Vect2D(const Vect2D& vect) : Vect2D(vect._x, vect._y) {}

XCoord Vect2D::x() const { return this->_x; }
void Vect2D::x(const XCoord x) { this->_x = x; }
YCoord Vect2D::y() const { return this->_y; }
void Vect2D::y(const YCoord y) { this->_y = y; }

bool Vect2D::operator==(const Vect2D& vect) const {
  // Returns true if both vectors have same x and y components
  return eq(this->_x, vect._x) && eq(this->_y, vect._y);
}

bool Vect2D::operator!=(const Vect2D& vect) const {
  // Returns true if vectors have different x or y components
  return !(*this == vect);
}

Vect2D Vect2D::operator+(const Vect2D& vect) const { return Vect2D(this->_x + vect._x, this->_y + vect._y); }

void Vect2D::operator+=(const Vect2D& vect) {
  this->_x += vect._x;
  this->_y += vect._y;
}

Vect2D Vect2D::operator-(const Vect2D& vect) const {
  // Implements vector subtraction
  // -: R^2 X R^2 -> R^2
  return Vect2D(this->_x - vect._x, this->_y - vect._y);
}

void Vect2D::operator-=(const Vect2D& vect) {
  // Implements vector subtraction and assignment
  this->_x -= vect._x;
  this->_y -= vect._y;
}

Vect2D Vect2D::operator*(const real value) const {
  // Implements scalar multiplication
  // *: R X R^2 -> R^2
  return Vect2D(this->_x * value, this->_y * value);
}

void Vect2D::operator*=(const real value) {
  // Implements scalar multiplication and assignment
  this->_x *= value;
  this->_y *= value;
}

void Vect2D::addScaledVector(const Vect2D& vect, const real scalar) {
  this->_x += vect._x * scalar;
  this->_y += vect._y * scalar;
}

void Vect2D::clear() {
  // Sets all components to 0
  this->_x = 0.0;
  this->_y = 0.0;
}
void Vect2D::invert() {
  // Sets all components to their additive inverse
  this->_x = -1.0 * this->_x;
  this->_y = -1.0 * this->_y;
}

void Vect2D::absMin(const real minValue) {
  /*
   * If the x or y of the vector falls within (-minValue, minValue),
   * set it to 0.0. Otherwise, leave them unchanged.
   */
  this->_x = ((-minValue < this->_x) && (this->_x < minValue)) ? 0.0 : this->_x;
  this->_y = ((-minValue < this->_y) && (this->_y < minValue)) ? 0.0 : this->_y;
}

Vect2D Vect2D::getXComponent() const { return Vect2D(this->_x, 0.0); }
Vect2D Vect2D::getYComponent() const { return Vect2D(0.0, this->_y); }

bool Vect2D::leftOf(const Vect2D& vect) const { return lt(this->_x, vect._x); }
bool Vect2D::rightOf(const Vect2D& vect) const { return gt(this->_x, vect._x); }
bool Vect2D::below(const Vect2D& vect) const { return lt(this->_y, vect._y); }
bool Vect2D::above(const Vect2D& vect) const { return gt(this->_y, vect._y); }

real Vect2D::distance(const Vect2D& vect) const {
  /*
   * Calculates Euclidean distance between two vectors.
   * Adapted from:
   * sqrt(pow((vect1.x() - vect2.x()), 2) + pow((vect1.y() - vect2.y()), 2));
   */
  real xDiff = this->_x - vect._x;
  real yDiff = this->_y - vect._y;
  return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

std::string Vect2D::to_string() const { return fmt::format("Vect2D({0}, {1})", this->_x, this->_y); }
