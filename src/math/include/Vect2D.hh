#pragma once

#include "Memory.hh"
#include "Real.hh"
#include "Types.hh"

/*
 * This code was adapted from cyclone-physics by Ian Millington.
 * cyclone-physics is released under the MIT license, and is copyright (c)
 * 2003-2009 Ian Millington.
 * cyclone-physics:
 * https://github.com/idmillington/cyclone-physics/
 * MIT License:
 * https://raw.githubusercontent.com/idmillington/cyclone-physics/master/LICENSE
 */

class Vect2D {
  /*
   * Implements a 2D vector of real (floating point) numbers.
   */
 public:
  Vect2D(const XCoord x, const YCoord y);
  // Vect2D(const Vect2D& vect);

  XCoord x() const;
  void x(const XCoord x);
  YCoord y() const;
  void y(const YCoord y);

  static Vect2D zero() { return Vect2D(0.0, 0.0); }

  bool operator==(const Vect2D& vect) const;
  bool operator!=(const Vect2D& other) const;
  Vect2D operator+(const Vect2D& vect) const;
  void operator+=(const Vect2D& vect);
  Vect2D operator-(const Vect2D& vect) const;
  void operator-=(const Vect2D& vect);
  Vect2D operator*(const real value) const;
  void operator*=(const real value);

  void addScaledVector(const Vect2D& vect, const real scalar);

  bool leftOf(const Vect2D& vect) const;
  bool rightOf(const Vect2D& vect) const;
  bool below(const Vect2D& vect) const;
  bool above(const Vect2D& vect) const;

  real getMagnitude() const;
  void clear();
  void invert();
  void absMin(const real minValue);
  Vect2D getXComponent() const;
  Vect2D getYComponent() const;
  real distance(const Vect2D& vect) const;
  string to_string() const;

 private:
  /*
   * Disallow vector operations on integer values; a user must consciously
   * convert any int to a real to use vector operations.
   * NOTE: by declaring these private and deleted, the compiler will match on
   * an inaccessible function (for outsiders) or raise an error for calling an
   * explicitly deleted function (for other Vect2Ds; this is preferred to
   * linker errors).
   */
  // TODO: I wanted to delete the default constructor to avoid any vectors being
  // created without explicit x/y values. It seems like I won't be able to do
  // this and also do call-by-value (which incurs copying)
  explicit Vect2D() = delete;
  explicit Vect2D(int x, int y) = delete;
  void operator*=(const int value) = delete;
  void addScaledVector(const Vect2D& vect, const int scalar) = delete;
  void addScaledVector(const Vect2D vect, const int scalar) = delete;
  void roundToZero(const int minValue) = delete;

  XCoord _x;
  YCoord _y;
};
