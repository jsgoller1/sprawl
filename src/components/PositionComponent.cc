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

void PositionComponent::setCenter(shared_ptr<Vect2D> center,
                                  const bool stayOnScreen) {
  if (this->validPosition(center)) {
    this->x = center->x;
    this->y = center->y;
  }
}

void PositionComponent::move(const shared_ptr<Vect2D> delta,
                             const bool stayOnScreen) {
  this->setCenter(
      shared_ptr<Vect2D>(new Vect2D(this->x + delta->x, this->y + delta->y)),
      stayOnScreen);
}

void PositionComponent::moveReverse(const shared_ptr<Vect2D> delta,
                                    const bool stayOnScreen) {
  shared_ptr<Vect2D> inverted = shared_ptr<Vect2D>(new Vect2D(delta));
  inverted->invert();
  this->move(inverted, stayOnScreen);
};

void PositionComponent::moveOnlyX(const shared_ptr<Vect2D> delta,
                                  const bool stayOnScreen) {
  shared_ptr<Vect2D> onlyX = shared_ptr<Vect2D>(new Vect2D(delta));
  onlyX->y = 0.0;
  this->move(onlyX, stayOnScreen);
};

void PositionComponent::moveReverseOnlyX(const shared_ptr<Vect2D> delta,
                                         const bool stayOnScreen) {
  shared_ptr<Vect2D> onlyX = shared_ptr<Vect2D>(new Vect2D(delta));
  onlyX->y = 0.0;
  this->moveReverse(onlyX, stayOnScreen);
};

void PositionComponent::moveOnlyY(const shared_ptr<Vect2D> delta,
                                  const bool stayOnScreen) {
  shared_ptr<Vect2D> onlyY = shared_ptr<Vect2D>(new Vect2D(delta));
  onlyY->x = 0.0;
  this->move(onlyY, stayOnScreen);
};

void PositionComponent::moveReverseOnlyY(const shared_ptr<Vect2D> delta,
                                         const bool stayOnScreen) {
  shared_ptr<Vect2D> onlyY = shared_ptr<Vect2D>(new Vect2D(delta));
  onlyY->x = 0.0;
  this->moveReverse(onlyY, stayOnScreen);
};

bool PositionComponent::validPosition(const shared_ptr<Vect2D> position) {
  return (0 <= position->x) && (position->x <= SCREEN_WIDTH) &&
         (0 <= position->y) && (position->y <= SCREEN_HEIGHT);
}
