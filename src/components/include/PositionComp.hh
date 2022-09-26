#pragma once
#include "Math.hh"
#include "Memory.hh"

class PositionComp {
 public:
  PositionComp(shared_ptr<Vect2D> center);
  PositionComp(const XCoord center_x, const YCoord center_y);

  XCoord getX();
  void setX(const XCoord center_x);
  YCoord getY();
  void setY(const YCoord center_y);
  shared_ptr<Vect2D> getCenter();
  void setCenter(shared_ptr<Vect2D> center);

  void move(const shared_ptr<Vect2D> delta);
  void reverseMove(const shared_ptr<Vect2D> delta);
  void moveOnlyX(const shared_ptr<Vect2D> vect);
  void reverseMoveOnlyX(const shared_ptr<Vect2D> vect);
  void moveOnlyY(const shared_ptr<Vect2D> vect);
  void reverseMoveOnlyY(const shared_ptr<Vect2D> vect);

 private:
  XCoord x;
  YCoord y;
};
