#pragma once
#include "Math.hh"
#include "Memory.hh"
#include "PositionTypes.hh"

class PositionComp {
 public:
  PositionComp(shared_ptr<Vect2D> center);
  PositionComp(const XCoord center_x, const YCoord center_y);

  XCoord getX();
  YCoord getY();
  void setX(const XCoord center_x);
  void setY(const YCoord center_y);
  shared_ptr<Vect2D> getCenter();
  void setCenter(shared_ptr<Vect2D> center);

  void updateX(const XCoord x);
  void updateY(const YCoord y);
  void updateCenter(shared_ptr<Vect2D> delta);

  void move(const shared_ptr<Vect2D> movement);

 private:
  XCoord x;
  YCoord y;
};

typedef shared_ptr<PositionComp> shared_ptr<PositionComp>;
