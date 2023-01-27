#pragma once

#include <memory>
#include <vector>

#include "BulletCollection.hh"
#include "BulletSpriteManager.hh"

// Fwd decls
class Bullet;
class Direction;
class DrawingProxy;
class Vect2D;

class LevelShootingProxy {
 public:
  LevelShootingProxy(BulletCollection& levelBullets);
  void shoot(const Direction& direction, const Vect2D& origin, const BulletColor color) const;

 private:
  BulletCollection& _levelBullets;
};
