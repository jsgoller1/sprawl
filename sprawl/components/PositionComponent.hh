#pragma once
#include "Component.hh"
#include "Identity.hh"
#include "Math.hh"
#include "Types.hh"

class PositionComponent : public Component {
 public:
  PositionComponent(const std::shared_ptr<Identity> ownerIdentity, const Vect2D& center);
  PositionComponent(const std::shared_ptr<Identity> ownerIdentity, const XCoord x = 0.0, const YCoord y = 0.0);

  PositionUnit x() const;
  void x(const PositionUnit x);
  PositionUnit y() const;
  void y(const PositionUnit y);
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
