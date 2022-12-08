#pragma once

#include "Line.hh"
#include "Logging.hh"
#include "Real.hh"
#include "Vect2D.hh"

// TODO: Maybe we also want to define class Box : public Rectangle

class Rectangle {
  /*
   * Rectangle is a data class that represents a geometric rectangle;
   * it is always aligned with the origin (line segments from its top left to
   * bottom left corner or bottom left to bottom right corners are always
   * parallel to the y-axis and x-axis, respectively)
   */
 public:
  Rectangle(const Vect2D& center, const PositionUnit height, const PositionUnit width);

  Vect2D getCenter() const;
  void setCenter(const Vect2D& newCenter);
  PositionUnit getHeight() const;
  void setHeight(const PositionUnit height);
  PositionUnit getWidth() const;
  void setWidth(const PositionUnit width);

  PositionUnit area() const;
  Line top() const;
  Line bottom() const;
  Line left() const;
  Line right() const;
  Vect2D topLeft() const;
  Vect2D topRight() const;
  Vect2D bottomLeft() const;
  Vect2D bottomRight() const;
  std::string toString() const;

 private:
  // Hide default constructor; every Rectangle needs to have the correct
  // attributes at creation time
  Rectangle() = delete;
  Vect2D _center = Vect2D::zero();
  PositionUnit _height;
  PositionUnit _width;
};
