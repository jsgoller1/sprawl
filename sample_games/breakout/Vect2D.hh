#pragma once

class Vect2D {
 public:
  Vect2D(const int x, const int y);
  int x = 0;
  int y = 0;
  bool above(const Vect2D& other);
  bool below(const Vect2D& other);
  bool left(const Vect2D& other);
  bool right(const Vect2D& other);
  Vect2D operator+(const Vect2D& vect) const;
  void operator+=(const Vect2D& vect);
  Vect2D operator-(const Vect2D& vect) const;
  void operator-=(const Vect2D& vect);
};
