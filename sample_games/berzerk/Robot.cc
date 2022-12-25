#include "Robot.hh"

#include "Direction.hh"

void Robot::aiBehavior(const Vect2D& playerPosition) {
  (void)playerPosition;
  //   // TODO: perhaps we should refactor this to functions that work on each state?
  //   if (this->_state == DYING || this->_state == DEAD) {
  //     // Nothing intelligent to do if we're dead.
  //     return;
  //   }

  //   Direction validFiringDirection = this->lineScan(playerPosition);
  //   if (validFiringDirection != Direction::None()) {
  //     this->useStandingAnimationSet();
  //     this->faceDirection(validFiringDirection);
  //     this->shoot(validFiringDirection, this->getPosition());
  //   } else {
  //     this->useMovingAnimationSet();
  //     this->faceDirection(this->getHeading(playerPosition));
  //     this->move();
  //   }
}

Direction Robot::lineScan(const GameObject& target) {
  (void)target;
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

  return Direction::None();
}

void Robot::move() {
  // Sometimes check if wall is in front of us, then set velocity
}
