#include "PlayerPositionProxy.hh"

#include "Direction.hh"
#include "Player.hh"
#include "Vect2D.hh"

static int absval(int val) { return val * ((val > 0) ? 1 : -1); }

PlayerPositionProxy::PlayerPositionProxy(const Player& player) : _player(player) {}

Vect2D PlayerPositionProxy::getPlayerPosition() const { return this->_player.getPosition(); }

Direction PlayerPositionProxy::lineScan(const Vect2D& currentPosition, const int errorMargin) const {
  /*
    UDLR: do the following interval overlap tests
      - our center's y vs target's y interval (aligned horizontally if overlapping)
      - our center's x vs target's x-interval (aligned vertically if overlapping)
    Diagonals:
      - Draw a line from our center to target's center. If the absval of the slope = 1, it is a perfect diagonal.
    Realistically, the slope can probably fall within a range (say 5/1 to 1/5) since we don't need to hit the target
    at their midpoint.

    If we make contact with the target, return the direction they're in relative to us. Else return Direction::None().
  */

  Vect2D playerPosition = this->_player.getPosition();
  // N or S
  if (absval(currentPosition.x - playerPosition.x) < errorMargin) {
    return (currentPosition.y > playerPosition.y) ? Direction::South() : Direction::North();
  }

  // W or E
  else if (absval(currentPosition.y - playerPosition.y) < errorMargin) {
  }

  // If the slope is 1 or -1, then the absval of difference between our x and their x should be the same for our y and
  // their y. To allow for a margin of error (e.g. suppose we want to be OK with slopes ranging from 5/1 to 1/5), we can
  // then check that the difference between abs(us.x - them.x) and abs(us.y - them.y) is within the margin (e.g.
  // within 5).

  // NE or SW
  else if (false) {
  }

  // NW or SE
  else if (false) {
  }

  // Otherwise, not on compass rose
  return Direction::None();
}
Direction PlayerPositionProxy::getPursuitHeading(const Vect2D& currentPosition) const {
  (void)currentPosition;
  return Direction::None();
}
