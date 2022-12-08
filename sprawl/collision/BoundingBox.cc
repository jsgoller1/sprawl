#include "BoundingBox.hh"

BoundingBox::BoundingBox(const Vect2D& center, const PositionUnit height, const PositionUnit width) {
  this->_box = Rectangle(center, height, width);
}

BoundingBox::BoundingBox(const Rectangle& box) { this->_box = Rectangle(box); }

BoundingBox::BoundingBox(const BoundingBox& boundingBox) { this->_box = Rectangle(boundingBox.box()); }

Rectangle BoundingBox::box() const { return this->_box; }

bool BoundingBox::checkCollision(const Vect2D& point) const {
  /*
   * Tests if we intersect with the given point; we can do this via a simple
   * range test against our own corners.
   */
  Rectangle box = this->_box;
  return rangeContainsVal(box.bottomLeft().x(), box.bottomRight().x(), point.x()) &&
         rangeContainsVal(box.bottomLeft().y(), box.topLeft().y(), point.y());
}
bool BoundingBox::checkCollision(const Line& line) const {
  /*
   * A line intersects a box if either endpoint falls inside the box, or if it
   * intersects with any of its sides. Note: it might be inefficient to test the
   * line against each of the four sides; we might be able to do a shortcut by
   * comparing the corners to the line somehow.
   */
  if (this->checkCollision(line.start()) || this->checkCollision(line.end())) {
    return true;
  }
  Rectangle box = this->_box;
  if (line.intersects(box.top()) || line.intersects(box.bottom()) || line.intersects(box.left()) ||
      line.intersects(box.right())) {
    return true;
  }
  return false;
}

bool BoundingBox::checkCollision(const BoundingBox& otherBox) const {
  /*
   * To check collisions with another box, pick whichever is smaller (either if
   * they're equal) and test if any of its corner points fall within the other
   * box. NOTE: SDL implements several functions and types we can use for
   * collision detection, but this works fine for now and I don't want the
   * dependency.
   */
  bool otherBiggerEq = gte(otherBox.box().area(), this->box().area());
  BoundingBox larger = (otherBiggerEq) ? otherBox : *this;
  BoundingBox smaller = (otherBiggerEq) ? *this : otherBox;

  return larger.checkCollision(smaller.box().topLeft()) || larger.checkCollision(smaller.box().bottomLeft()) ||
         larger.checkCollision(smaller.box().topRight()) || larger.checkCollision(smaller.box().bottomRight());
}

std::string BoundingBox::toString() const { return fmt::format("BoundingBox({0})", this->_box.toString()); }
