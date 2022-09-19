#pragma once
#include "Memory.hh"

typedef int PositionUnit;

typedef struct Point {
  PositionUnit x;
  PositionUnit y;
} Point;
typedef shared_ptr<Point> PointSPtr;

class PositionComp {
 public:
  PositionComp(PointSPtr center);
  PositionComp(const PositionUnit center_x, const PositionUnit center_y);
  void setCenter(PointSPtr center);
  PointSPtr getCenter();
  PositionUnit getX();
  void setX(const PositionUnit center_x);
  PositionUnit getY();
  void setY(const PositionUnit center_y);

 private:
  PositionUnit x;
  PositionUnit y;
};

typedef shared_ptr<PositionComp> PositionCompSPtr;
