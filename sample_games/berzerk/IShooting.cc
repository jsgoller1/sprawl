#include "IShooting.hh"

void IShooting::shoot(const Direction& direction, const Vect2D& origin) {
  // TODO: include delay to enforce rate of fire
  this->_shootingProxy.shoot(direction, origin);
}
