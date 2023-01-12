#pragma once

#include "BulletSpriteManager.hh"
#include "LevelShootingProxy.hh"

// Fwd decl
class Direction;
class Vect2D;

class IShooting {
 public:
  IShooting(LevelShootingProxy& shootingProxy);
  void shoot(const Direction& direction, const Vect2D& origin, const BulletColor color);

 private:
  // IShooting
  LevelShootingProxy& _shootingProxy;
};
