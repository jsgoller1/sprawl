#pragma once

#include "Math.hh"
#include "Real.hh"
#include "Types.hh"
#include "json.hpp"

class DuplicationBehavior {
 public:
  DuplicationBehavior(const nlohmann::json& jsonBody);
  // DuplicationBehavior() : _count(0), _max(0), _xOffset(0), _yOffset(0) {}
  void next();
  bool done() const;
  Vect2D getOffset();
  PositionUnit getXOffset();
  PositionUnit getYOffset();
  int getCount();
  int getCurr();

 private:
  int _curr;
  int _count;
  PositionUnit _xOffset;
  PositionUnit _yOffset;
};
