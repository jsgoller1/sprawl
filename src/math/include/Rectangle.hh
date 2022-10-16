#pragma once

#include "Line.hh"
#include "Memory.hh"
#include "Real.hh"
#include "Vect2D.hh"

// TODO: Maybe we also want to define class Box : public Rectangle

class Rectangle {
  /*
   * Rectangle is an immutable data class that represents a geometric rectangle
   */
 public:
  Rectangle(const PositionUnit height, const PositionUnit width,
            const shared_ptr<Vect2D> center);
  Rectangle(const shared_ptr<Vect2D> topLeft, const shared_ptr<Vect2D> topRight,
            const shared_ptr<Vect2D> bottomLeft,
            const shared_ptr<Vect2D> bottomRight);
  Rectangle(const shared_ptr<Rectangle> rectangle);
  PositionUnit getHeight() const;
  PositionUnit getWidth() const;
  shared_ptr<const Vect2D> getCenter() const;
  shared_ptr<const Vect2D> getTopLeft() const;
  shared_ptr<const Vect2D> getTopRight() const;
  shared_ptr<const Vect2D> getBottomLeft() const;
  shared_ptr<const Vect2D> getBottomRight() const;

 private:
  // Hide default constructor; every Rectangle needs to have the correct
  // attributes at creation time
  Rectangle() = delete;
  void Init(const PositionUnit height, const PositionUnit width,
            const shared_ptr<Vect2D> center, const shared_ptr<Vect2D> topLeft,
            const shared_ptr<Vect2D> topRight,
            const shared_ptr<Vect2D> bottomLeft,
            const shared_ptr<Vect2D> bottomRight);
  bool isValidRectangle();
  PositionUnit height;
  PositionUnit width;
  shared_ptr<const Vect2D> center;
  shared_ptr<const Vect2D> topLeft;
  shared_ptr<const Vect2D> topRight;
  shared_ptr<const Vect2D> bottomLeft;
  shared_ptr<const Vect2D> bottomRight;
};
