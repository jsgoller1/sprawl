#include "PositionComponent.hh"

PositionComponent::PositionComponent(shared_ptr<Point> center) {
  this->x = center->x;
  this->y = center->y;
}

shared_ptr<Point> PositionComponent::getCenter() {
  return shared_ptr<Point>(new Point{.x = this->x, .y = this->y});
}
void PositionComponent::setCenter(shared_ptr<Point> center) {
  this->x = center->x;
  this->y = center->y;
}

void PositionComponent::updateX(const PositionUnit x) { this->x += x; }
void PositionComponent::updateY(const PositionUnit y) { this->y += y; }
void PositionComponent::updateCenter(shared_ptr<Point> delta) {
  this->x += delta->x;
  this->y += delta->y;
}

void PositionComponent::move(const shared_ptr<Point> movement) {
  this->x += movement->x;
  this->y += movement->y;
}
