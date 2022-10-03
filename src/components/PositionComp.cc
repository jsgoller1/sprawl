#include "PositionComp.hh"

PositionComp::PositionComp(shared_ptr<Vect2D> center) {
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
shared_ptr<Vect2D> PositionComp::getCenter() {
  return shared_ptr<Vect2D>(new Vect2D(this->x, this->y));
}
void PositionComp::setCenter(shared_ptr<Vect2D> center) {
  this->x = center->x;
  this->y = center->y;
}

void PositionComp::move(const shared_ptr<Vect2D> movement) {
  this->x += movement->x;
  this->y += movement->y;
}

void PositionComp::reverseMove(const shared_ptr<Vect2D> delta) {
  shared_ptr<Vect2D> inverted = shared_ptr<Vect2D>(new Vect2D(delta));
  inverted->invert();
  this->move(inverted);
};
void PositionComp::moveOnlyX(const shared_ptr<Vect2D> vect) {
  shared_ptr<Vect2D> onlyX = shared_ptr<Vect2D>(new Vect2D(vect));
  onlyX->y = 0.0;
  this->move(onlyX);
};
void PositionComp::reverseMoveOnlyX(const shared_ptr<Vect2D> vect) {
  shared_ptr<Vect2D> onlyX = shared_ptr<Vect2D>(new Vect2D(vect));
  onlyX->y = 0.0;
  this->reverseMove(onlyX);
};
void PositionComp::moveOnlyY(const shared_ptr<Vect2D> vect) {
  shared_ptr<Vect2D> onlyY = shared_ptr<Vect2D>(new Vect2D(vect));
  onlyY->x = 0.0;
  this->move(onlyY);
};
void PositionComp::reverseMoveOnlyY(const shared_ptr<Vect2D> vect) {
  shared_ptr<Vect2D> onlyY = shared_ptr<Vect2D>(new Vect2D(vect));
  onlyY->x = 0.0;
  this->reverseMove(onlyY);
};
