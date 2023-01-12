#include "IShooting.hh"

IShooting::IShooting(LevelShootingProxy& shootingProxy) : _shootingProxy(shootingProxy) {}

void IShooting::shoot(const Direction& direction, const Vect2D& origin, const BulletColor color) {
  // TODO: include delay to enforce rate of fire
  this->_shootingProxy.shoot(direction, origin, color);
}
