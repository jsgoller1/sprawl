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
  bool low2Intersects = (lte(low1, low2) && lte(low2, hi1));
  bool hi2Intersects = (lte(low1, hi2) && lte(hi2, hi1));
  bool containedIn1 = (lte(low1, low2) && lte(hi2, hi1));
  bool containedIn2 = (lte(low2, low1) && lte(hi1, hi2));
  return low2Intersects || hi2Intersects || containedIn1 || containedIn2;
}

// TODO: Floating point comparison is hard; here, we're just doing
// a margin-of-error test and calling it a day. Followups:
// - CS:APP (Bryant et al), sec 3.11
// - https://floating-point-gui.de/errors/comparison/
bool eq(const real& real1, const real& real2) {
  real diff = real1 - real2;
  return ((-FLOAT_EQ_ACCEPTABLE_MARGIN_OF_ERROR < diff) &&
          (diff < FLOAT_EQ_ACCEPTABLE_MARGIN_OF_ERROR));
}
bool neq(const real& real1, const real& real2) { return false; };
// TODO: Implement these
bool lte(const real& real1, const real& real2) { return false; };
bool gte(const real& real1, const real& real2) { return false; }

Vect2D::Vect2D() {
  this->x = 0.0;
  this->y = 0.0;
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

Vect2D::Vect2D(shared_ptr<Direction> direction) {
  this->x = direction->getX();
  this->y = direction->getY();
}

bool Vect2D::operator==(const Vect2D& vect) const {
  // Returns true if both vectors have same x and y components
  return eq(this->x, vect.x) && eq(this->y, vect.y);
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

void Vect2D::addScaledVector(const Vect2D& vect, const real scalar) {
  this->x += vect.x * scalar;
  this->y += vect.y * scalar;
}

void Vect2D::clear() {
  // Sets all components to 0
  this->x = 0.0;
  this->y = 0.0;
}
void Vect2D::invert() {
  // Sets all components to their additive inverse
  this->x = -1.0 * this->x;
  this->y = -1.0 * this->y;
}

void Vect2D::roundToZero(const real minValue) {
  // if a value falls within a certain range, set it to zero.
  // TODO: We may want to generalize this
  // to a generic roundUp or roundDown method; for now,
  // we only need rounding down to zero.
  this->x = ((-minValue < this->x) && (this->x < minValue)) ? 0.0 : this->x;
  this->y = ((-minValue < this->y) && (this->y < minValue)) ? 0.0 : this->y;
}

bool Direction::operator==(const Direction& dir) const {
  // Returns true if both vectors have same x and y components
  return eq(this->x, dir.x) && eq(this->y, dir.y);
}

string Vect2D::to_string() {
  return "Vect2D(x: " + std::to_string(this->x) +
         ", y: " + std::to_string(this->y) + ")";
}
