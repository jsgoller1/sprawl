#include "Rectangle.hh"

Rectangle::Rectangle(const Vect2D& center, const PositionUnit height, const PositionUnit width)
    : _center(Vect2D(center)), _height(height), _width(width) {
  this->_topLeft = Vect2D(this->_center.x() - (this->_width / 2.0), this->_center.y() + (this->_height / 2.0));
  this->_topRight = Vect2D(this->_center.x() + (this->_width / 2.0), this->_center.y() + (this->_height / 2.0));
  this->_bottomLeft = Vect2D(this->_center.x() - (this->_width / 2.0), this->_center.y() - (this->_height / 2.0));
  this->_bottomRight = Vect2D(this->_center.x() + (this->_width / 2.0), this->_center.y() - (this->_height / 2.0));
  this->isValidRectangle();
}

Rectangle::Rectangle(const Vect2D& topLeft, const Vect2D& topRight, const Vect2D& bottomLeft, const Vect2D& bottomRight)
    : _topLeft(Vect2D(topLeft)),
      _topRight(Vect2D(topRight)),
      _bottomLeft(Vect2D(bottomLeft)),
      _bottomRight(Vect2D(bottomRight)) {
  this->_height = Line(this->_topLeft, this->_bottomLeft).length();
  this->_width = Line(this->_topLeft, this->_topRight).length();
  this->_center = Vect2D(this->_bottomLeft.x() + this->_width / 2.0, this->_bottomLeft.y() + this->_height / 2.0);
}

/*
Rectangle::Rectangle(const Rectangle& rect) {
  // Only valid rectangles can exist, so we don't need to re-validate its
  // attributes when copying.
  this->_height = rect.height();
  this->_width = rect.width();
  this->_center = Vect2D(rect.center());
  this->_topLeft = Vect2D(rect.topLeft());
  this->_topRight = Vect2D(rect.topRight());
  this->_bottomLeft = Vect2D(rect.bottomLeft());
  this->_bottomRight = Vect2D(rect.bottomRight());
}
*/

PositionUnit Rectangle::area() const { return this->_height * this->_width; }
PositionUnit Rectangle::height() const { return this->_height; }
PositionUnit Rectangle::width() const { return this->_width; }
Line Rectangle::top() const { return Line(this->_topLeft, this->_topRight); }
Line Rectangle::bottom() const { return Line(this->_bottomLeft, this->_bottomRight); }
Line Rectangle::left() const { return Line(this->_topLeft, this->_bottomLeft); }
Line Rectangle::right() const { return Line(this->_topRight, this->_bottomRight); }
Vect2D Rectangle::center() const { return this->_center; }
Vect2D Rectangle::topLeft() const { return this->_topLeft; }
Vect2D Rectangle::topRight() const { return this->_topRight; }
Vect2D Rectangle::bottomLeft() const { return this->_bottomLeft; }
Vect2D Rectangle::bottomRight() const { return this->_bottomRight; }

string Rectangle::toString() const {
  return fmt::format("Rectangle(topLeft: {0}, topRight: {1}, bottomLeft: {2}, bottomRight: {3})",
                     this->topLeft().to_string(), this->topRight().to_string(), this->bottomLeft().to_string(),
                     this->bottomRight().to_string());
}

bool Rectangle::isValidRectangle() const {
  bool isValid = true;

  // Sanity check on height and width
  isValid &= this->_height > 0;
  isValid &= this->_width > 0;
  LOG_DEBUG_SYS(MATH, "Rectangle, sanity check on height and width: {}", isValid);

  // Confirm points are positioned correctly
  isValid &= this->_topLeft.leftOf(this->_topRight);
  isValid &= this->_bottomLeft.leftOf(this->_bottomRight);
  isValid &= this->_topLeft.above(this->_bottomLeft);
  isValid &= this->_topRight.above(this->_bottomRight);
  LOG_DEBUG_SYS(MATH, "Rectangle, points are positioned correctly: {}", isValid);

  // Confirm lefts and rights are width apart
  Line topLine = Line(this->_topLeft, this->_topRight);
  Line bottomLine = Line(this->_bottomLeft, this->_bottomRight);
  isValid &= eq(topLine.length(), this->_width);
  isValid &= eq(bottomLine.length(), this->_width);
  LOG_DEBUG_SYS(MATH, "Rectangle, lefts and rights are width apart: {}", isValid);

  // Confirm tops and bottoms are height apart
  Line leftLine = Line(this->_topLeft, this->_bottomLeft);
  Line rightLine = Line(this->_topRight, this->_bottomRight);
  isValid &= eq(leftLine.length(), this->_height);
  isValid &= eq(rightLine.length(), this->_height);
  LOG_DEBUG_SYS(MATH, "Rectangle, tops and bottoms are height apart: {}", isValid);

  // Confirm center is actually centered
  isValid &= Line(this->_center, this->_topLeft).displacement() == Vect2D(-this->_width / 2.0, this->_height / 2.0);
  isValid &= Line(this->_center, this->_bottomLeft).displacement() == Vect2D(-this->_width / 2.0, -this->_height / 2.0);
  isValid &= Line(this->_center, this->_topRight).displacement() == Vect2D(this->_width / 2.0, this->_height / 2.0);
  isValid &= Line(this->_center, this->_bottomRight).displacement() == Vect2D(this->_width / 2.0, -this->_height / 2.0);
  LOG_DEBUG_SYS(MATH, "Rectangle, center is actually centered: {}", isValid);

  assert(isValid);
  return isValid;
}
