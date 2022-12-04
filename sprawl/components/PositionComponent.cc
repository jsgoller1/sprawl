
#include "PositionComponent.hh"

PositionComponent::PositionComponent(const std::shared_ptr<Identity> ownerIdentity, const XCoord x, const YCoord y)
    : Component(ownerIdentity) {
  this->_x = x;
  this->_y = y;
}

PositionUnit PositionComponent::x() const { return this->_x; }
void PositionComponent::x(const PositionUnit x) { this->_x = x; }
PositionUnit PositionComponent::y() const { return this->_y; }
void PositionComponent::y(const PositionUnit y) { this->_y = y; }

Vect2D PositionComponent::getCenter() { return Vect2D(this->x(), this->y()); }

void PositionComponent::setCenter(const Vect2D& center) {
  this->_x = center.x();
  this->_y = center.y();
}

void PositionComponent::move(const Vect2D& delta) {
  this->setCenter(Vect2D(this->_x + delta.x(), this->_y + delta.y()));
}

void PositionComponent::moveReverse(const Vect2D& delta) {
  Vect2D inverted = Vect2D(delta);
  inverted.invert();
  this->move(inverted);
};

void PositionComponent::moveOnlyX(const Vect2D& delta) { this->move(delta.getXComponent()); };

void PositionComponent::moveReverseOnlyX(const Vect2D& delta) { this->moveReverse(delta.getYComponent()); };

void PositionComponent::moveOnlyY(const Vect2D& delta) { this->move(delta.getYComponent()); };

void PositionComponent::moveReverseOnlyY(const Vect2D& delta) { this->moveReverse(delta.getYComponent()); };
