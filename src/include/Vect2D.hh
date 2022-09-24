#pragma once
/*
 * This code was adapted from cyclone-physics by Ian Millington.
 * cyclone-physics is released under the MIT license, and is copyright (c)
 * 2003-2009 Ian Millington.
 * cyclone-physics:
 * https://github.com/idmillington/cyclone-physics/
 * MIT License:
 * https://raw.githubusercontent.com/idmillington/cyclone-physics/master/LICENSE
 */

#include "Memory.hh"
#include "Types.hh"

class Vect2D {
 public:
  Vect2D();
  Vect2D(XCoord x, YCoord y);
  Vect2D(const Vect2D& vect);
  Vect2D(shared_ptr<Vect2D> vect);
  ~Vect2D();
  XCoord x;
  YCoord y;

  bool operator==(const Vect2D& other) const;
  bool operator!=(const Vect2D& other) const;
  shared_ptr<Vect2D> operator+(const Vect2D& vect) const;
  void operator+=(const Vect2D& vect);
  shared_ptr<Vect2D> operator-(const Vect2D& vect) const;
  void operator-=(const Vect2D& vect);
  shared_ptr<Vect2D> operator*(const real value) const;
  void operator*=(const real value);

  void clear();
  void invert();
};
