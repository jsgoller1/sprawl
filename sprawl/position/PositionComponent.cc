
#include "PositionComponent.hh"

#include "Actor.hh"

PositionComponent::PositionComponent(const Vect2D& center, const PositionUnit height, const PositionUnit width)
    : Component(), _area(Rectangle(center, height, width)) {}

std::string PositionComponent::toString() const { return "PositionComponent " + this->getUUID(); }

PositionUnit PositionComponent::x() const { return this->_area.getCenter().x(); }
void PositionComponent::x(const PositionUnit x) { this->_area.getCenter().x(x); }
PositionUnit PositionComponent::y() const { return this->_area.getCenter().y(); }
void PositionComponent::y(const PositionUnit y) { this->_area.getCenter().y(y); }

Vect2D PositionComponent::getCenter() const { return this->_area.getCenter(); }
void PositionComponent::setCenter(const Vect2D& center) { this->_area.setCenter(center); }

PositionUnit PositionComponent::getWidth() { return this->_area.getWidth(); }
void PositionComponent::setWidth(const PositionUnit width) { this->_area.setWidth(width); }
PositionUnit PositionComponent::getHeight() { return this->_area.getHeight(); }
void PositionComponent::setHeight(const PositionUnit height) { this->_area.setHeight(height); }

Rectangle& PositionComponent::getArea() { return this->_area; }
void PositionComponent::setArea(const Rectangle& area) { this->_area = Rectangle(area); }

Vect2D PositionComponent::getTopLeft() const { return this->_area.topLeft(); }

void PositionComponent::move(const Vect2D& delta) {
  this->setCenter(Vect2D(this->_area.getCenter().x() + delta.x(), this->_area.getCenter().y() + delta.y()));
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
