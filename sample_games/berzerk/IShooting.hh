#pragma once

#include "ShootingProxy.hh"

// Fwd decls
class Direction;
class Vect2D;

class IShooting {
 public:
  IShooting(const ShootingProxy& proxy) : _proxy(proxy) {}
  void shoot(const Direction& direction, const Vect2D& origin) {
    // TODO: include delay to enforce rate of fire
    this->_proxy.shoot(direction, origin);
  }

 private:
  const ShootingProxy& _proxy;
};
