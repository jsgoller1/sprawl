#pragma once
#include "Component.hh"
#include "Identity.hh"
#include "Math.hh"
#include "Memory.hh"
#include "Types.hh"

class PositionComponent : public Component {
 public:
  PositionComponent(const shared_ptr<Identity> ownerIdentity, const Vect2D& center);
  PositionComponent(const shared_ptr<Identity> ownerIdentity, const XCoord x = 0.0, const YCoord y = 0.0);

  PositionUnit x() const { return this->_x; }
  void x(const PositionUnit x) { this->_x = x; }
  PositionUnit y() const { return this->_y; }
  void y(const PositionUnit y) { this->_y = y; }
  Vect2D getCenter();
  void setCenter(const Vect2D& center);

  void move(const Vect2D& delta);
  void moveReverse(const Vect2D& delta);
  void moveOnlyX(const Vect2D& vect);
  void moveReverseOnlyX(const Vect2D& vect);
  void moveOnlyY(const Vect2D& vect);
  void moveReverseOnlyY(const Vect2D& vect);

 private:
  XCoord _x;
  YCoord _y;
};
