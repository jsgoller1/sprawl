#include "IShooting.hh"

#include "ShootingProxy.hh"

void IShooting::shoot(const Direction& direction, const Vect2D& origin) {
  // TODO: include delay to enforce rate of fire
  this->_proxy.shoot(direction, origin);
}
