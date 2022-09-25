#include "Math.hh"

/*
 * This code was adapted from cyclone-physics by Ian Millington.
 * cyclone-physics is released under the MIT license, and is copyright (c)
 * 2003-2009 Ian Millington.
 * cyclone-physics:
 * https://github.com/idmillington/cyclone-physics/
 * MIT License:
 * https://raw.githubusercontent.com/idmillington/cyclone-physics/master/LICENSE
 */

// TODO: This method works only for lines that are presumed to be perpendictular
// or parallel to the coordinate axes. Can another version be written that takes
// 4 points and can reliably test intersection regardless of orientation?
// (Could we just apply a 2D rotation matrix to each point and then do the same
// test?)
bool areLinesIntersecting(const PositionUnit low1, const PositionUnit hi1,
                          const PositionUnit low2, const PositionUnit hi2) {
  /*
   To do 2D collision testing, we need to do two separate 1D line intersection
   tests; if both intersect, a 2D collision occurs.
   For two straight lines A and B (each with start and end points l and r,
   though this works for vertical lines too), we have four cases to check:
    - The right side of A intersects with B:
      B.l <= A.r <= B.r
    - The left side of A intersects with B:
      B.l <= A.l <= B.r
    - A falls completely in B:
      B.l <= A.l < A.r <= B.r
    - B falls completely within A:
      A.l <= B.l < B.r <= A.r
  */
  bool low2Intersects = ((low1 <= low2) && (low2 <= hi1));
  bool hi2Intersects = ((low1 <= hi2) && (hi2 <= hi1));
  bool containedIn1 = ((low1 <= low2) && (hi2 <= hi1));
  bool containedIn2 = ((low2 <= low1) && (hi1 <= hi2));
  return low2Intersects || hi2Intersects || containedIn1 || containedIn2;
}

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
