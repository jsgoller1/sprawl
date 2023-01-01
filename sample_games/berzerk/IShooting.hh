#pragma once

#include "ShootingProxy.hh"

// Fwd decl
class Direction;
class Vect2D;

class IShooting {
 public:
  IShooting(ShootingProxy& shootingProxy);
  void shoot(const Direction& direction, const Vect2D& origin);

 private:
  // IShooting
  ShootingProxy& _shootingProxy;
};
