#include <PositionComp.hh>

PositionComp::PositionComp(const PositionUnit x, const PositionUnit y) {
  this->x = x;
  this->y = y;
}

PositionUnit PositionComp::getX() { return this->x; }
void PositionComp::setX(const PositionUnit x) { this->x = x; }
PositionUnit PositionComp::getY() { return this->y; }
void PositionComp::setY(const PositionUnit y) { this->y = y; }
