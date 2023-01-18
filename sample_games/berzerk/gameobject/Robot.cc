#include "Robot.hh"

#include "Direction.hh"

#define ROBOT_DEFAULT_WIDTH 40
#define ROBOT_DEFAULT_HEIGHT 55

Robot::Robot(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy,
             DrawingProxy& drawingProxy, const RobotSpriteManager& robotSpriteManager)
    : GameObject(position, velocity), IShooting(shootingProxy) {
  this->_robotAnimationSet = std::unique_ptr<RobotAnimationSet>(new RobotAnimationSet(robotSpriteManager));
  this->_drawingComponent = std::unique_ptr<AnimatedDrawingComponent>(
      new AnimatedDrawingComponent(this->getPositionComponent(), ROBOT_DEFAULT_HEIGHT, ROBOT_DEFAULT_WIDTH,
                                   drawingProxy, this->_robotAnimationSet->idle()));
}

AnimatedDrawingComponent& Robot::getDrawingComponent() const { return *this->_drawingComponent; }

void Robot::resolveCollision(GameObject& target) {
  (void)target;
  // TODO: I'd prefer we didn't do either state or animation setting here; both already have
  // respective update functions, and should be done there.
  // TODO: Maybe we should have an event queue of some kind and state updates process events on that queue?
  if (this->_state != CharacterState::DYING) {
    this->_state = CharacterState::DYING;
    // this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->getDyingSequence());
  }
}

void Robot::update(const time_ms deltaT) { this->_drawingComponent->updateAnimationSequence(deltaT); }

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
