#include "IShooting.hh"

#include "Configs.hh"

IShooting::IShooting(LevelShootingProxy& shootingProxy) : _shootingProxy(shootingProxy) {}

void IShooting::shoot(const Direction& direction, const Vect2D& origin, const BulletColor color) {
  // NOTE: If bullet spaws directly on player or robot, it will kill them instantly; we must spawn it at an offset
  // TODO:
  Vect2D offsetOrigin = origin + (Vect2D(direction) * BULLET_SPAWN_OFFSET_DISTANCE_PX);
  this->_shootingProxy.shoot(direction, offsetOrigin, color);
}
