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
  this->xCoord = 0.0;
  this->yCoord = 0.0;
}
Vect2D::Vect2D(XCoord x, YCoord y) {
  this->xCoord = x;
  this->yCoord = y;
}
Vect2D::Vect2D(const Vect2D& vect) {
  this->xCoord = vect.x();
  this->yCoord = vect.y();
}
Vect2D::Vect2D(shared_ptr<Vect2D> vect) {
  this->xCoord = vect->x();
  this->yCoord = vect->y();
}

Vect2D::Vect2D(shared_ptr<Direction> direction) {
  this->xCoord = direction->getX();
  this->yCoord = direction->getY();
}

XCoord Vect2D::x() const { return this->xCoord; }
void Vect2D::x(const XCoord x) { this->xCoord = x; }
YCoord Vect2D::y() const { return this->yCoord; }
void Vect2D::y(const YCoord y) { this->yCoord = y; }

bool Vect2D::operator==(const Vect2D& vect) const {
  // Returns true if both vectors have same x and y components
  return eq(this->y(), vect.x()) && eq(this->y(), vect.y());
}
bool Vect2D::operator==(const shared_ptr<Vect2D> vect) const {
  return this->operator==(*vect.get());
}

bool Vect2D::operator!=(const Vect2D& vect) const {
  // Returns true if vectors have different x or y components
  return !(*this == vect);
}
bool Vect2D::operator!=(const shared_ptr<Vect2D> vect) const {
  return this->operator!=(*vect.get());
}

shared_ptr<Vect2D> Vect2D::operator+(const Vect2D& vect) const {
  return shared_ptr<Vect2D>(
      new Vect2D(this->xCoord + vect.x(), this->yCoord + vect.y()));
}
shared_ptr<Vect2D> Vect2D::operator+(const shared_ptr<Vect2D> vect) const {
  return this->operator+(*vect.get());
}

void Vect2D::operator+=(const Vect2D& vect) {
  this->xCoord += vect.x();
  this->yCoord += vect.y();
}
void Vect2D::operator+=(const shared_ptr<Vect2D> vect) {
  this->operator+=(*vect.get());
}

shared_ptr<Vect2D> Vect2D::operator-(const Vect2D& vect) const {
  // Implements vector subtraction
  // -: R^2 X R^2 -> R^2
  return shared_ptr<Vect2D>(
      new Vect2D(this->xCoord - vect.x(), this->yCoord - vect.y()));
}
shared_ptr<Vect2D> Vect2D::operator-(const shared_ptr<Vect2D> vect) const {
  this->operator-(*vect.get());
}

void Vect2D::operator-=(const Vect2D& vect) {
  // Implements vector subtraction and assignment
  this->xCoord -= vect.x();
  this->yCoord -= vect.y();
}
void Vect2D::operator-=(const shared_ptr<Vect2D> vect) {
  this->operator-=(*vect.get());
}

shared_ptr<Vect2D> Vect2D::operator*(const real value) const {
  // Implements scalar multiplication
  // *: R X R^2 -> R^2
  return shared_ptr<Vect2D>(
      new Vect2D(this->xCoord * value, this->yCoord * value));
}

void Vect2D::operator*=(const real value) {
  // Implements scalar multiplication and assignment
  this->xCoord *= value;
  this->yCoord *= value;
}

void Vect2D::addScaledVector(const Vect2D& vect, const real scalar) {
  this->xCoord += vect.x * scalar;
  this->yCoord += vect.y * scalar;
}

void Vect2D::addScaledVector(const Vect2D& vect, const int scalar) {
  this->addScaledVector(vect, real(scalar));
}

void Vect2D::clear() {
  // Sets all components to 0
  this->xCoord = 0.0;
  this->yCoord = 0.0;
}
void Vect2D::invert() {
  // Sets all components to their additive inverse
  this->xCoord = -1.0 * this->xCoord;
  this->yCoord = -1.0 * this->yCoord;
}

void Vect2D::roundToZero(const real minValue) {
  // if a value falls within a certain range, set it to zero.
  // TODO: We may want to generalize this
  // to a generic roundUp or roundDown method; for now,
  // we only need rounding down to zero.
  this->xCoord = ((-minValue < this->xCoord) && (this->xCoord < minValue))
                     ? 0.0
                     : this->xCoord;
  this->yCoord = ((-minValue < this->yCoord) && (this->yCoord < minValue))
                     ? 0.0
                     : this->yCoord;
}

string Vect2D::to_string() {
  return "Vect2D(x: " + std::to_string(this->xCoord) +
         ", y: " + std::to_string(this->yCoord) + ")";
}

shared_ptr<Vect2D> Vect2D::getXComponent() {
  return shared_ptr<Vect2D>(new Vect2D(this->xCoord, 0.0));
}

shared_ptr<Vect2D> Vect2D::getYComponent() {
  return shared_ptr<Vect2D>(new Vect2D(0.0, this->yCoord));
}

bool Vect2D::leftOf() const {}
bool Vect2D::rightOf() const {}
bool Vect2D::above() const {}
bool Vect2D::below() const {}
