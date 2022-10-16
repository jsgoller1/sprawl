#pragma once

#include "Direction.hh"
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
 public:
  Vect2D();
  Vect2D(XCoord x, YCoord y);
  Vect2D(const Vect2D& vect);
  Vect2D(shared_ptr<Vect2D> vect);
  Vect2D(shared_ptr<Direction> direction);

  XCoord x() const;
  void x(const XCoord x);
  YCoord y() const;
  void y(const YCoord y);

  static shared_ptr<Vect2D> zero() {
    return shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
  }

  bool operator==(const Vect2D& vect) const;
  bool operator==(const shared_ptr<Vect2D> vect) const;

  bool operator!=(const Vect2D& other) const;
  bool operator!=(const shared_ptr<Vect2D> vect) const;

  shared_ptr<Vect2D> operator+(const Vect2D& vect) const;
  shared_ptr<Vect2D> operator+(const shared_ptr<Vect2D> vect) const;

  void operator+=(const Vect2D& vect);
  void operator+=(const shared_ptr<Vect2D> vect);

  shared_ptr<Vect2D> operator-(const Vect2D& vect) const;
  shared_ptr<Vect2D> operator-(const shared_ptr<Vect2D> vect) const;

  void operator-=(const Vect2D& vect);
  void operator-=(const shared_ptr<Vect2D> vect);

  shared_ptr<Vect2D> operator*(const real value) const;
  shared_ptr<Vect2D> operator*(const shared_ptr<Vect2D> vect) const;

  void operator*=(const real value);

  void addScaledVector(const Vect2D& vect, const real scalar);
  void addScaledVector(const shared_ptr<Vect2D> vect, const real scalar);
  void addScaledVector(const Vect2D& vect, const int scalar);
  void addScaledVector(const shared_ptr<Vect2D> vect, const int scalar);

  shared_ptr<Direction> getDirection();
  real getMagnitude();
  void clear();
  void invert();
  void roundToZero(const real minValue);
  shared_ptr<Vect2D> getXComponent();
  shared_ptr<Vect2D> getYComponent();
  string to_string();

 private:
  // Disallow creation of vectors from integer coordinates.
  explicit Vect2D(int x, int y);

  XCoord xCoord;
  YCoord yCoord;
};
