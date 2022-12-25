#pragma once

// Fwd decls
class Direction;
class Vect2D;

class ShootingProxy {
 public:
  virtual ~ShootingProxy();
  virtual void shoot(const Direction& direction, const Vect2D& origin) const = 0;
};
