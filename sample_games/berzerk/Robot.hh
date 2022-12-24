#pragma once

#include "GameObject.hh"
#include "IAnimation.hh"
#include "ICollision.hh"
#include "IShooting.hh"

class Robot : public GameObject, public ICollision, public IShooting, public IAnimation {
 public:
  void aiBehavior(const Vect2D& playerPosition) {
    // TODO: perhaps we should refactor this to functions that work on each state?
    if (this->_state == DYING || this->_state == DEAD) {
      // Nothing intelligent to do if we're dead.
      return;
    }

    Direction validFiringDirection = this->lineScan(playerPosition);
    if (validFiringDirection != Direction::None()) {
      this->useStandingAnimationSet();
      this->faceDirection(validFiringDirection);
      this->shoot(validFiringDirection, this->getPosition());
    } else {
      this->useMovingAnimationSet();
      this->faceDirection(this->getHeading(playerPosition));
      this->move();
    }
  }

 private:
  enum RobotState { IDLE, MOVING, SHOOTING, DYING, DEAD };
  RobotState _state;
  // Has: heading direction

  Direction lineScan(const GameObject& target) {
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
  void move() {
    // Sometimes check if wall is in front of us, then set velocity
  }
};
