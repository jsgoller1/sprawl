#pragma once

#include <memory>
#include <vector>

#include "BulletSpriteManager.hh"

// Fwd decls
class Bullet;
class Direction;
class DrawingProxy;
class Vect2D;

class LevelShootingProxy {
 public:
  LevelShootingProxy(std::vector<std::shared_ptr<Bullet>>& _levelBullets,
                     const BulletSpriteManager& bulletSpriteManager, DrawingProxy& _drawingProxy);
  void shoot(const Direction& direction, const Vect2D& origin, const BulletColor color) const;

 private:
  DrawingProxy& _drawingProxy;
  std::vector<std::shared_ptr<Bullet>>& _levelBullets;
  // TODO: Maybe we should have a BulletSpriteManager instead, idk?
  // Robots will have their own bullet sprites.
  const BulletSpriteManager& _bulletSpriteManager;
};
