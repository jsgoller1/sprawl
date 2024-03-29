#include "Vect2D.hh"

Vect2D::Vect2D(const int x, const int y) : x(x), y(y) {}

bool Vect2D::above(const Vect2D& other) { return this->y > other.y; }
bool Vect2D::below(const Vect2D& other) { return this->y < other.y; }
bool Vect2D::left(const Vect2D& other) { return this->x < other.x; }
bool Vect2D::right(const Vect2D& other) { return this->x > other.x; }

Vect2D Vect2D::operator+(const Vect2D& vect) const { return Vect2D(this->x + vect.x, this->y + vect.y); }

void Vect2D::operator+=(const Vect2D& vect) {
  this->x += vect.x;
  this->y += vect.y;
}

Vect2D Vect2D::operator-(const Vect2D& vect) const {
  // Implements vector subtraction
  // -: R^2 X R^2 -> R^2
  return Vect2D(this->x - vect.x, this->y - vect.y);
}

void Vect2D::operator-=(const Vect2D& vect) {
  // Implements vector subtraction and assignment
  this->x -= vect.x;
  this->y -= vect.y;
}
