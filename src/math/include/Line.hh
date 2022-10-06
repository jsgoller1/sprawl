#pragma once

#include "MathHelpers.hh"
#include "Real.hh"
#include "Types.hh"
#include "Vect2D.hh"

class Line {
  /*
   *
   */
 public:
  Line(const Vect2D& start, const Vect2D& end);
  Line(const Line& line);

  Vect2D start() const;
  Vect2D end() const;

  real slope() const;
  real length() const;
  Vect2D displacement() const;
  bool intersects(const Vect2D& point) const;
  bool intersects(const Line& line) const;

 private:
  Line() = delete;
  const Vect2D _start;
  const Vect2D _end;
};
