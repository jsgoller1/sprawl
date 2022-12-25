#pragma once

// Fwd decls
class ShootingProxy;
class Direction;
class Vect2D;

class IShooting {
 public:
  IShooting(const ShootingProxy& proxy) : _proxy(proxy) {}
  void shoot(const Direction& direction, const Vect2D& origin);

 private:
  const ShootingProxy& _proxy;
};
