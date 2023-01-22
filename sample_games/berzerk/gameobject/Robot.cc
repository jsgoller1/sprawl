#include "Robot.hh"

#include "Direction.hh"

Robot::Robot(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy,
             DrawingProxy& drawingProxy, const PlayerPositionProxy& playerPositionProxy,
             const RobotSpriteManager& robotSpriteManager)
    : GameObject(position, velocity), IShooting(shootingProxy), _playerPositionProxy(playerPositionProxy) {
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

void Robot::update(const time_ms deltaT) {
  this->_state = this->getNewState(this->_state);
  this->setVelocity(this->getNewVelocity(this->_state));
  this->updateAnimation(deltaT, this->_state);
  this->shootingBehavior(deltaT);
  this->move();
}

CharacterState Robot::getNewState(const CharacterState currentState) const {
  /*
   * As soon as the player is within range, robots either start shooting or moving to a firing axis.
   */
  if (currentState == CharacterState::DEAD) {
    return currentState;
  }

  if (currentState == CharacterState::DYING) {
    if (this->getDrawingComponent().getAnimationSequence().isComplete()) {
      return CharacterState::DEAD;
    }
    return currentState;
  }
  if (!this->withinRangeOfPlayer()) {
    return CharacterState::IDLE;
  }
  if (this->getShootingDirection() != Direction::None()) {
    return CharacterState::SHOOTING;
  }
  return CharacterState::MOVING;
}

Vect2D Robot::getNewVelocity(const CharacterState state) const {
  if (state != CharacterState::MOVING) {
    return Vect2D::zero();
  }
  // TODO: This is obviously wrong, we need some way to get a heading / facing direction
  return Vect2D(ROBOT_MOVE_SPEED, ROBOT_MOVE_SPEED);
}

void Robot::updateAnimation(const time_ms deltaT, const CharacterState state) {
  Direction facingDirection = this->_playerPositionProxy.getPursuitHeading(this->getPosition());
  switch (state) {
    case CharacterState::IDLE:
      this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->idle());
      break;
    case CharacterState::MOVING:
      this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->moving(facingDirection));
      break;
    case CharacterState::SHOOTING:
      this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->shooting(facingDirection));
      break;
    case CharacterState::DYING:
      this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->dying());
      break;
    case CharacterState::DEAD:
      this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->dead());
      break;
  }
  this->_drawingComponent->updateAnimationSequence(deltaT);
}

void Robot::shootingBehavior(const time_ms deltaT) {
  this->_sinceLastShot += deltaT;
  if (this->_state == CharacterState::SHOOTING && this->_sinceLastShot > ROBOT_SHOOT_DELAY_MS) {
    Direction shootingDirection = this->getShootingDirection();
    this->_sinceLastShot = 0;
    this->shoot(shootingDirection, Vect2D::zero(), GREEN);
  }
}

bool Robot::withinRangeOfPlayer() const { return false; }

Direction Robot::getHeadingDirection() const {
  //
  return Direction::None();
}

Direction Robot::getShootingDirection() const { return this->_playerPositionProxy.lineScan(this->getPosition()); }
