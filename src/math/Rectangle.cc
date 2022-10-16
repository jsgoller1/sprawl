#include "Rectangle.hh"

Rectangle::Rectangle(const PositionUnit height, const PositionUnit width,
                     const shared_ptr<Vect2D> center) {}
Rectangle::Rectangle(const shared_ptr<Vect2D> topLeft,
                     const shared_ptr<Vect2D> topRight,
                     const shared_ptr<Vect2D> bottomLeft,
                     const shared_ptr<Vect2D> bottomRight) {}
Rectangle::Rectangle(const shared_ptr<Rectangle> rectangle) {}

PositionUnit Rectangle::getHeight() const { return this->height; }
PositionUnit Rectangle::getWidth() const { return this->width; }
shared_ptr<const Vect2D> Rectangle::getCenter() const { return this->center; }
shared_ptr<const Vect2D> Rectangle::getTopLeft() const { return this->topLeft; }
shared_ptr<const Vect2D> Rectangle::getTopRight() const {
  return this->topRight;
}
shared_ptr<const Vect2D> Rectangle::getBottomLeft() const {
  return this->bottomLeft;
}
shared_ptr<const Vect2D> Rectangle::getBottomRight() const {
  return this->bottomRight;
}

void Rectangle::Init(const PositionUnit height, const PositionUnit width,
                     const shared_ptr<Vect2D> center,
                     const shared_ptr<Vect2D> topLeft,
                     const shared_ptr<Vect2D> topRight,
                     const shared_ptr<Vect2D> bottomLeft,
                     const shared_ptr<Vect2D> bottomRight) {
  this->center = shared_ptr<const Vect2D>(new Vect2D(center));
  this->topLeft = shared_ptr<const Vect2D>(new Vect2D(topLeft));
  this->topRight = shared_ptr<const Vect2D>(new Vect2D(topRight));
  this->bottomLeft = shared_ptr<const Vect2D>(new Vect2D(bottomLeft));
  this->bottomRight = shared_ptr<const Vect2D>(new Vect2D(bottomRight));
  this->isValidRectangle();
}

bool Rectangle::isValidRectangle() {
  bool isValid = true;
  // Confirm points are positioned correctly
  isValid &= this->topLeft->leftOf(topRight);
  isValid &= this->bottomLeft->leftOf(bottomRight);
  isValid &= this->topLeft->above(bottomLeft);
  isValid &= this->topRight->above(bottomRight);

  // Confirm lefts and rights are width apart
  Line topLine = Line(this->topLeft, this->topRight);
  Line bottomLine = Line(this->bottomLeft, this->bottomRight);
  isValid &= *(topLine.getLength().get()) == Vect2D(width, 0.0);
  isValid &= *(bottomLine.getLength().get()) == Vect2D(width, 0.0);

  // Confirm tops and bottoms are height apart
  Line leftLine = Line(this->topLeft, this->bottomLeft);
  Line rightLine = Line(this->topRight, this->bottomRight);
  isValid &= *(leftLine.getLength().get()) == Vect2D(0.0, height);
  isValid &= *(rightLine.getLength().get()) == Vect2D(0.0, height);

  // Confirm center is actually centered

  assert(isValid);
  return isValid;
}
