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

  PositionUnit getX();
  PositionUnit getY();
  void setX(const PositionUnit center_x);
  void setY(const PositionUnit center_y);
  PointSPtr getCenter();
  void setCenter(PointSPtr center);

  void updateX(const PositionUnit x);
  void updateY(const PositionUnit y);
  void updateCenter(PointSPtr delta);

 private:
  PositionUnit x;
  PositionUnit y;
};

typedef shared_ptr<PositionComp> PositionCompSPtr;
