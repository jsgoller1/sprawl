#include "PlayerPositionProxy.hh"

#include "Direction.hh"
#include "Math.hh"
#include "Player.hh"
#include "Vect2D.hh"

PlayerPositionProxy::PlayerPositionProxy(const Player& player) : _player(player) {}

Vect2D PlayerPositionProxy::getPlayerPosition() const { return this->_player.getPosition(); }

Direction PlayerPositionProxy::lineScan(const Vect2D& currentPosition, const int errorMargin) const {
  /*
  // If the slope is 1 or -1, then the absval of difference between our x and their x should be the same for our y and
  // their y. To allow for a margin of error (e.g. suppose we want to be OK with slopes ranging from 5/1 to 1/5), we can
  // then check that the difference between abs(us.x - them.x) and abs(us.y - them.y) is within the margin (e.g.
  // within 5).
  */

  Vect2D playerPosition = this->_player.getPosition();
  // N or S
  if (absval(currentPosition.x - playerPosition.x) <= errorMargin) {
    return (currentPosition.y > playerPosition.y) ? Direction::South() : Direction::North();
  }

  // W or E
  else if (absval(currentPosition.y - playerPosition.y) <= errorMargin) {
    return (currentPosition.x > playerPosition.x) ? Direction::West() : Direction::East();
  }

  // TODO: Diagonal shooting
  /*
  // NE or SW
  else if (false) {
  }

  // NW or SE
  else if (false) {
  }
  */

  // Otherwise, not on compass rose
  return Direction::None();
}
