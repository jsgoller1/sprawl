#pragma once
#include "Vect2D.hh"

class IMovement {
 public:
  virtual Vect2D getVelocity() const;
  virtual void setVelocity(const Vect2D& velocity);

 private:
  Vect2D _velocity;
};
