#include "Rectangle.hh"

#include <cassert>

Rectangle::Rectangle(const Vect2D& center, const PositionUnit height, const PositionUnit width)
    : _center(Vect2D(center)), _height(height), _width(width) {}

PositionUnit Rectangle::getHeight() const { return this->_height; }
void Rectangle::setHeight(const PositionUnit height) { this->_height = height; }
PositionUnit Rectangle::getWidth() const { return this->_width; }
void Rectangle::setWidth(const PositionUnit width) { this->_width = width; }

Vect2D Rectangle::getCenter() const { return this->_center; }
void Rectangle::setCenter(const Vect2D& newCenter) { this->_center = newCenter; }

PositionUnit Rectangle::area() const { return this->_height * this->_width; }
Vect2D Rectangle::topLeft() const { return this->_center + Vect2D(-(this->_width / 2), this->_height / 2); }
Vect2D Rectangle::topRight() const { return this->_center + Vect2D(this->_width / 2, this->_height / 2); }
Vect2D Rectangle::bottomLeft() const { return this->_center + Vect2D(-(this->_width / 2), -(this->_height / 2)); }
Vect2D Rectangle::bottomRight() const { return this->_center + Vect2D(this->_width / 2, -(this->_height / 2)); }
Line Rectangle::top() const { return Line(this->topLeft(), this->topRight()); }
Line Rectangle::bottom() const { return Line(this->bottomLeft(), this->bottomRight()); }
Line Rectangle::left() const { return Line(this->topLeft(), this->bottomLeft()); }
Line Rectangle::right() const { return Line(this->topRight(), this->bottomRight()); }

std::string Rectangle::toString() const {
  return fmt::format("Rectangle(topLeft: {0}, topRight: {1}, bottomLeft: {2}, bottomRight: {3})",
                     this->topLeft().to_string(), this->topRight().to_string(), this->bottomLeft().to_string(),
                     this->bottomRight().to_string());
}
