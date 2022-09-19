#pragma once
#include "Memory.hh"

typedef int PositionUnit;

class PositionComp {
 public:
  PositionComp(const PositionUnit x, const PositionUnit y);
  void setPosition(const PositionUnit x, const PositionUnit y);
  PositionUnit getX();
  void setX(const PositionUnit x);
  PositionUnit getY();
  void setY(const PositionUnit y);

 private:
  PositionUnit x;
  PositionUnit y;
};

typedef shared_ptr<PositionComp> PositionCompSPtr;
