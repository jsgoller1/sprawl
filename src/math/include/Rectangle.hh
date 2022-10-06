#pragma once

#include "Line.hh"
#include "Logging.hh"
#include "Memory.hh"
#include "Real.hh"
#include "Vect2D.hh"

// TODO: Maybe we also want to define class Box : public Rectangle

class Rectangle {
  /*
   * Rectangle is an immutable data class that represents a geometric rectangle;
   * it is always aligned with the origin (line segments from its top left to
   * bottom left corner or bottom left to bottom right corners are always
   * parallel to the y-axis and x-axis, respectively)
   */
 public:
  Rectangle(const Vect2D& center, const PositionUnit height, const PositionUnit width);
  Rectangle(const Vect2D& topLeft, const Vect2D& topRight, const Vect2D& bottomLeft, const Vect2D& bottomRight);
  // Rectangle(const Rectangle& rectangle);

  PositionUnit area() const;
  PositionUnit height() const;
  PositionUnit width() const;
  Line top() const;
  Line bottom() const;
  Line left() const;
  Line right() const;
  Vect2D center() const;
  Vect2D topLeft() const;
  Vect2D topRight() const;
  Vect2D bottomLeft() const;
  Vect2D bottomRight() const;
  string toString() const;

 private:
  // Hide default constructor; every Rectangle needs to have the correct
  // attributes at creation time
  Rectangle() = delete;
  bool isValidRectangle() const;
  Vect2D _center = Vect2D::zero();
  PositionUnit _height;
  PositionUnit _width;
  Vect2D _topLeft = Vect2D::zero();
  Vect2D _topRight = Vect2D::zero();
  Vect2D _bottomLeft = Vect2D::zero();
  Vect2D _bottomRight = Vect2D::zero();
};
