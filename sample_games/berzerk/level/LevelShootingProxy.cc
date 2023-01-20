#include "LevelShootingProxy.hh"

#include <iostream>

#include "Bullet.hh"
#include "Direction.hh"
#include "DrawingProxy.hh"
#include "Vect2D.hh"

LevelShootingProxy::LevelShootingProxy(std::vector<std::shared_ptr<Bullet>>& levelBullets,
                                       const BulletSpriteManager& bulletSpriteManager, DrawingProxy& drawingProxy)
    : _drawingProxy(drawingProxy), _levelBullets(levelBullets), _bulletSpriteManager(bulletSpriteManager) {}

void LevelShootingProxy::shoot(const Direction& direction, const Vect2D& origin, const BulletColor color) const {
  /*
   * Creates bullet heading in direction with default bullet velocity.
   */

  std::cout << "Adding bullet at " << origin.x << "," << origin.y << std::endl;

  this->_levelBullets.push_back(
      std::make_shared<Bullet>(origin, direction, this->_drawingProxy, this->_bulletSpriteManager, color));
}
