#include "Vect2D.hh"

/*
 * This code was adapted from cyclone-physics by Ian Millington.
 * cyclone-physics is released under the MIT license, and is copyright (c)
 * 2003-2009 Ian Millington.
 * cyclone-physics:
 * https://github.com/idmillington/cyclone-physics/
 * MIT License:
 * https://raw.githubusercontent.com/idmillington/cyclone-physics/master/LICENSE
 */

Vect2D::Vect2D() {
  this->x = 0;
  this->y = 0;
}
Vect2D::Vect2D(XCoord x, YCoord y) {
  this->x = x;
  this->y = y;
}
Vect2D::Vect2D(const Vect2D& vect) {
  this->x = vect.x;
  this->y = vect.y;
}
Vect2D::Vect2D(shared_ptr<Vect2D> vect) {
  this->x = vect->x;
  this->y = vect->y;
}

bool Vect2D::operator==(const Vect2D& vect) const {
  // Returns true if both vectors have same x and y components
  return this->x == vect.x && this->y == vect.y;
}
bool Vect2D::operator!=(const Vect2D& vect) const {
  // Returns true if vectors have different x or y components
  return !(*this == vect);
}

shared_ptr<Vect2D> Vect2D::operator+(const Vect2D& vect) const {
  // Implements vector addition
  // +: R^2 X R^2 -> R^2
  return shared_ptr<Vect2D>(new Vect2D(this->x + vect.x, this->y + vect.y));
}

void Vect2D::operator+=(const Vect2D& vect) {
  // Implements vector addition and assignment
  this->x += vect.x;
  this->y += vect.y;
}

shared_ptr<Vect2D> Vect2D::operator-(const Vect2D& vect) const {
  // Implements vector subtraction
  // -: R^2 X R^2 -> R^2
  return shared_ptr<Vect2D>(new Vect2D(this->x - vect.x, this->y - vect.y));
}

void Vect2D::operator-=(const Vect2D& vect) {
  // Implements vector subtraction and assignment
  this->x -= vect.x;
  this->y -= vect.y;
}

shared_ptr<Vect2D> Vect2D::operator*(const real value) const {
  // Implements scalar multiplication
  // *: R X R^2 -> R^2
  return shared_ptr<Vect2D>(new Vect2D(this->x * value, this->y * value));
}

void Vect2D::operator*=(const real value) {
  // Implements scalar multiplication and assignment
  this->x *= value;
  this->y *= value;
}

void Vect2D::clear() {
  // Sets all components to 0
  this->x = 0;
  this->y = 0;
}
void Vect2D::invert() {
  // Sets all components to their additive inverse
  this->x = -this->x;
  this->y = -this->y;
}
