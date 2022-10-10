#pragma once
#include "Math.hh"
#include "Memory.hh"
#include "Types.hh"

class PositionComponent {
 public:
  PositionComponent(shared_ptr<Vect2D> center);
  PositionComponent(const XCoord x, const YCoord y);

  PositionUnit getX() const { return this->x; }
  void setX(const PositionUnit x) { this->x = x; }
  PositionUnit getY() const { return this->y; }
  void setY(const PositionUnit y) { this->y = y; }
  shared_ptr<Vect2D> getCenter();
  void setCenter(shared_ptr<Vect2D> center);

  void move(const shared_ptr<Vect2D> delta);
  void moveReverse(const shared_ptr<Vect2D> delta);
  void moveOnlyX(const shared_ptr<Vect2D> vect);
  void moveReverseOnlyX(const shared_ptr<Vect2D> vect);
  void moveOnlyY(const shared_ptr<Vect2D> vect);
  void moveReverseOnlyY(const shared_ptr<Vect2D> vect);

 private:
  XCoord x;
  YCoord y;
};
