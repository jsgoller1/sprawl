#pragma once
#include "Memory.hh"

typedef int PositionUnit;

typedef struct Vect2D {
  PositionUnit x;
  PositionUnit y;
} Vect2D;

class PositionComp {
 public:
  PositionComp(shared_ptr<Vect2D> center);
  PositionComp(const PositionUnit center_x, const PositionUnit center_y);

  PositionUnit getX();
  PositionUnit getY();
  void setX(const PositionUnit center_x);
  void setY(const PositionUnit center_y);
  shared_ptr<Vect2D> getCenter();
  void setCenter(shared_ptr<Vect2D> center);

  void updateX(const PositionUnit x);
  void updateY(const PositionUnit y);
  void updateCenter(shared_ptr<Vect2D> delta);

  void move(const shared_ptr<Vect2D> movement);

 private:
  PositionUnit x;
  PositionUnit y;
};

typedef shared_ptr<PositionComp> PositionCompSPtr;
