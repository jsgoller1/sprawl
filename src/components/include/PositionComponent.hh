#pragma once
#include "Math.hh"
#include "Memory.hh"
#include "Types.hh"

class PositionComponent {
 public:
  PositionComponent(shared_ptr<Vect2D> center);
  PositionComponent(const XCoord x = 0.0, const YCoord y = 0.0);

  PositionUnit getX() const { return this->x; }
  void setX(const PositionUnit x) { this->x = x; }
  PositionUnit getY() const { return this->y; }
  void setY(const PositionUnit y) { this->y = y; }
  shared_ptr<Vect2D> getCenter();
  void setCenter(shared_ptr<Vect2D> center, const bool stayOnScreen = true);

  void move(const shared_ptr<Vect2D> delta, const bool stayOnScreen = true);
  void moveReverse(const shared_ptr<Vect2D> delta,
                   const bool stayOnScreen = true);
  void moveOnlyX(const shared_ptr<Vect2D> vect, const bool stayOnScreen = true);
  void moveReverseOnlyX(const shared_ptr<Vect2D> vect,
                        const bool stayOnScreen = true);
  void moveOnlyY(const shared_ptr<Vect2D> vect, const bool stayOnScreen = true);
  void moveReverseOnlyY(const shared_ptr<Vect2D> vect,
                        const bool stayOnScreen = true);
  bool validPosition(const shared_ptr<Vect2D> position);

 private:
  XCoord x;
  YCoord y;
};
