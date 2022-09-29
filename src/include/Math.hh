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

#include <cfloat>

#include "Memory.hh"
#include "Types.hh"

/*
 NOTE: I wanted to avoid using floating point operations anywhere, because I
don't want to deal with:
 - Precision issues and comparison
 - Casting from integral to floating point correctly and vice versa
 - Convering to int screen coordinates for SDL.
As an aside, the DOOM engine was implemented entirely with integer operations
(DOOM Game Engine Black Book, p.48) and smoothly did nearly everything we'll
want to do. If necessary, we can go down the FP rabbit hole later on.

That being said, our current physics implementation uses drag coefficients which
need to support multiplication / addition / etc; we could do this by
implementing a fraction type with numerators and denominators, but I feel like
that's overengineering.

So here's the strategy moving forward:
- We don't have a performance problem that requires attention until we have an
actual performance problem.
- Everything is a real number / double unless otherwise stated.
- Real number comparisons must use the below functions. We cannot
programmatically enforce this unless we implement real as a class, which feels
like overkill.
- If something _isn't_ a real (e.g. arr index) or can be more simply handled as
an integer (time_ms), it gets its own type via a class def or typedef. No
'naked ints' or inline int values. The idea here is to make types more explicit
and catch accidental conversion as easily as possible.
- Conversion of reals to ints for SDL's sake (screen coordinates, texture sizes,
etc) must happen as close to the SDL boundary as possible.

*/

#define FLOAT_EQ_ACCEPTABLE_MARGIN_OF_ERROR 0.00000001
bool eq(const real& real1, const real& real2);
bool neq(const real& real1, const real& real2);
bool lte(const real& real1, const real& real2);
bool gte(const real& real1, const real& real2);

#define MAX(x, y) ((x < y) ? y : x)
#define MIN(x, y) ((x > y) ? y : x)

bool areLinesIntersecting(const PositionUnit low1, const PositionUnit hi1,
                          const PositionUnit low2, const PositionUnit hi2);

class Vect2D {
 public:
  Vect2D();
  Vect2D(XCoord x, YCoord y);
  Vect2D(const Vect2D& vect);
  Vect2D(shared_ptr<Vect2D> vect);
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

  void addScaledVector(const Vect2D& vect, const real scalar);
  void addScaledVector(const Vect2D& vect, const int scalar) {
    this->addScaledVector(vect, real(scalar));
  }
  void addScaledVector(const Vect2D& vect, const time_ms scalar) {
    this->addScaledVector(vect, real(scalar));
  }

  void getDirection();
  void getMagnitude();
  void clear();
  void invert();

  static shared_ptr<Vect2D> zero() {
    return shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
  }

 private:
  // Disallow creation of vectors from integer coordinates.
  explicit Vect2D(int x, int y);
};

class Direction {
 public:
  static shared_ptr<Direction> None() {
    return shared_ptr<Direction>(new Direction(0.0, 0.0));
  }
  static shared_ptr<Direction> Up() {
    return shared_ptr<Direction>(new Direction(0.0, -1.0));
  }
  static shared_ptr<Direction> Down() {
    return shared_ptr<Direction>(new Direction(0.0, 1.0));
  }
  static shared_ptr<Direction> Left() {
    return shared_ptr<Direction>(new Direction(-1.0, 0.0));
  }
  static shared_ptr<Direction> Right() {
    return shared_ptr<Direction>(new Direction(-1.0, 0.0));
  }
  static shared_ptr<Direction> LeftUp() {
    return shared_ptr<Direction>(new Direction(-1.0, -1.0));
  }
  static shared_ptr<Direction> RightUp() {
    return shared_ptr<Direction>(new Direction(1.0, -1.0));
  }
  static shared_ptr<Direction> LeftDown() {
    return shared_ptr<Direction>(new Direction(-1.0, 1.0));
  }
  static shared_ptr<Direction> RightDown() {
    return shared_ptr<Direction>(new Direction(1.0, 1.0));
  }
  bool operator==(const Direction& other) const;

 private:
  explicit Direction(XCoord x, XCoord y) : x(x), y(y) {}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
  // These fields are in fact used, we just never access them directly; we are
  // using static methods to treat various values for Direction as constants.
  // See Effective C++, item 18 for details.
  XCoord x;
  YCoord y;
#pragma clang diagnostic pop
};

/*
class Force {
 public:
  Force(const Direction& direction, const Magnitude magnitude)
      : direction(direction), magnitude(magnitude){};
  Direction direction;
  Magnitude magnitude;
  static shared_ptr<Force> zero() {
    return shared_ptr<Force>(new Force(DIR_NONE, 0.0));
  }
};
*/
