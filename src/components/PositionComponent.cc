#include "PositionComponent.hh"

PositionComponent::PositionComponent(shared_ptr<Vect2D> center) {
  this->x = center->x;
  this->y = center->y;
}
PositionComponent::PositionComponent(const XCoord x, const YCoord y) {
  this->x = x;
  this->y = y;
}

shared_ptr<Vect2D> PositionComponent::getCenter() {
  return shared_ptr<Vect2D>(new Vect2D(this->x, this->y));
}

void PositionComponent::setCenter(shared_ptr<Vect2D> center) {
  this->x = center->x;
  this->y = center->y;
}

void PositionComponent::move(const shared_ptr<Vect2D> movement) {
  this->x += movement->x;
  this->y += movement->y;
}

void PositionComponent::moveReverse(const shared_ptr<Vect2D> delta) {
  shared_ptr<Vect2D> inverted = shared_ptr<Vect2D>(new Vect2D(delta));
  inverted->invert();
  this->move(inverted);
};

void PositionComponent::moveOnlyX(const shared_ptr<Vect2D> vect) {
  shared_ptr<Vect2D> onlyX = shared_ptr<Vect2D>(new Vect2D(vect));
  onlyX->y = 0.0;
  this->move(onlyX);
};

void PositionComponent::moveReverseOnlyX(const shared_ptr<Vect2D> vect) {
  shared_ptr<Vect2D> onlyX = shared_ptr<Vect2D>(new Vect2D(vect));
  onlyX->y = 0.0;
  this->moveReverse(onlyX);
};

void PositionComponent::moveOnlyY(const shared_ptr<Vect2D> vect) {
  shared_ptr<Vect2D> onlyY = shared_ptr<Vect2D>(new Vect2D(vect));
  onlyY->x = 0.0;
  this->move(onlyY);
};

void PositionComponent::moveReverseOnlyY(const shared_ptr<Vect2D> vect) {
  shared_ptr<Vect2D> onlyY = shared_ptr<Vect2D>(new Vect2D(vect));
  onlyY->x = 0.0;
  this->moveReverse(onlyY);
};
