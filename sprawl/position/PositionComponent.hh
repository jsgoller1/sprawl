#pragma once
#include "Component.hh"
#include "Math.hh"
#include "Types.hh"

static constexpr char POSITION_COMPONENT_NAME[] = "PositionComponent";

// fwd decls
class Actor;

class PositionComponent : public Component {
 public:
  PositionComponent(const Vect2D& center = Vect2D::zero(), const PositionUnit height = 1.0,
                    const PositionUnit width = 1.0);

  std::string toString() const override;

  // Getters / setters
  // Forwarding
  PositionUnit x() const;
  void x(const PositionUnit x);
  PositionUnit y() const;
  void y(const PositionUnit y);
  Vect2D getCenter() const;
  Vect2D getTopLeft() const;
  void setCenter(const Vect2D& center);
  Rectangle& getArea();
  void setArea(const Rectangle& area);
  PositionUnit getWidth();
  void setWidth(const PositionUnit width);
  PositionUnit getHeight();
  void setHeight(const PositionUnit height);

  // Special behavior
  void move(const Vect2D& delta);
  void moveReverse(const Vect2D& delta);
  void moveOnlyX(const Vect2D& vect);
  void moveReverseOnlyX(const Vect2D& vect);
  void moveOnlyY(const Vect2D& vect);
  void moveReverseOnlyY(const Vect2D& vect);

 private:
  Rectangle _area = Rectangle(Vect2D::zero(), 0.0, 0.0);
};
