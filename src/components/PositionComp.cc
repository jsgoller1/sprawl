#include <PositionComp.hh>

PositionComp::PositionComp(PointSPtr center) {
  this->x = center->x;
  this->y = center->y;
}
PositionComp::PositionComp(const PositionUnit center_x,
                           const PositionUnit center_y) {
  this->x = center_x;
  this->y = center_y;
}

PositionUnit PositionComp::getX() { return this->x; }
PositionUnit PositionComp::getY() { return this->y; }
void PositionComp::setX(const PositionUnit x) { this->x = x; }
void PositionComp::setY(const PositionUnit y) { this->y = y; }
PointSPtr PositionComp::getCenter() {
  return PointSPtr(new Point{.x = this->x, .y = this->y});
}
void PositionComp::setCenter(PointSPtr center) {
  this->x = center->x;
  this->y = center->y;
}

void PositionComp::updateX(const PositionUnit x) { this->x += x; }
void PositionComp::updateY(const PositionUnit y) { this->y += y; }
void PositionComp::updateCenter(PointSPtr delta) {
  this->x += delta->x;
  this->y += delta->y;
}

void PositionComp::move(const PointSPtr movement) {
  this->x += movement->x;
  this->y += movement->y;
}
