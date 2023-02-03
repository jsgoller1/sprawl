#include "Robot.hh"

#include <iostream>

#include "Direction.hh"
#include "Math.hh"
#include "WallCollisionProxy.hh"

Robot::Robot(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy,
             DrawingProxy& drawingProxy, const PlayerPositionProxy& playerPositionProxy,
             const RobotSpriteManager& robotSpriteManager, const WallCollisionProxy& wallCollisionProxy,
             const RobotWallAvoidancePolicy avoidancePolicy)
    : GameObject(position, velocity),
      IShooting(shootingProxy),
      _playerPositionProxy(playerPositionProxy),
      _wallCollisionProxy(wallCollisionProxy),
      _avoidancePolicy(avoidancePolicy),
      _isAvoiding(this->shouldAvoidWalls()) {
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
    this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->dying());
  }
}

void Robot::update(const time_ms deltaT, const bool forceIdle) {
  this->_sinceLastShot += deltaT;
  this->_state = (forceIdle ? CharacterState::IDLE : this->getNewState(this->_state));
  switch (this->_state) {
    case CharacterState::DEAD:
      this->stateBehaviorDead();
      break;
    case CharacterState::DYING:
      this->stateBehaviorDying();
      break;
    case CharacterState::IDLE:
      this->stateBehaviorIdle();
      break;
    case CharacterState::MOVING:
      this->_isAvoiding = this->shouldAvoidWalls();
      this->stateBehaviorMoving();
      break;
    case CharacterState::SHOOTING:
      this->stateBehaviorShooting();
      break;
  }
  this->_drawingComponent->updateAnimationSequence(deltaT);
}

CharacterState Robot::getNewState(const CharacterState currentState) const {
  /*
   * As soon as the player is within range, robots either start shooting or moving to a firing axis.
   */
  bool playerInRange = this->withinRangeOfPlayer();
  bool playerShootable = this->getShootingDirection() != Direction::None();

  if (currentState == CharacterState::DEAD) {
    return currentState;
  }
  if (currentState == CharacterState::DYING) {
    return (this->getDrawingComponent().getAnimationSequence().isComplete()) ? CharacterState::DEAD
                                                                             : CharacterState::DYING;
  }
  if (playerInRange && playerShootable) {
    return CharacterState::SHOOTING;
  }

  std::cout << "Next move would kill robot? "
            << this->_wallCollisionProxy.test(*this, Vect2D(this->getMovingDirection()) * ROBOT_MOVE_SPEED * 4)
            << std::endl;
  std::cout << "isAvoiding? " << this->_isAvoiding << std::endl;
  bool nextMoveKillsRobot =
      this->_wallCollisionProxy.test(*this, Vect2D(this->getMovingDirection()) * ROBOT_MOVE_SPEED * 4);

  if (playerInRange && !(this->_isAvoiding && nextMoveKillsRobot)) {
    return CharacterState::MOVING;
  }

  return CharacterState::IDLE;
}

void Robot::stateBehaviorDead() {
  this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->dead());
  this->setPosition(Vect2D(-2000, -2000));
}

void Robot::stateBehaviorDying() {
  this->getDrawingComponent().setHeight(ROBOT_DYING_HEIGHT);
  this->getDrawingComponent().setWidth(ROBOT_DYING_WIDTH);
  this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->dying());
}

void Robot::stateBehaviorIdle() { this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->idle()); }

void Robot::stateBehaviorMoving() {
  Direction facingDirection = this->getMovingDirection();
  this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->moving(facingDirection));
  this->setVelocity(Vect2D(facingDirection) * ROBOT_MOVE_SPEED);
  this->move();
}

void Robot::stateBehaviorShooting() {
  this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->shooting(this->getShootingDirection()));
  if (this->_sinceLastShot > ROBOT_SHOOT_DELAY_MS) {
    this->_sinceLastShot = 0;
    this->shoot(this->getShootingDirection(), this->getPosition());
  }
}

bool Robot::withinRangeOfPlayer() const {
  return this->getPosition().distance(this->_playerPositionProxy.getPlayerPosition()) <= ROBOT_PURSUIT_DISTANCE_PX;
}

Direction Robot::getShootingDirection() const {
  return this->_playerPositionProxy.lineScan(this->getPosition(), ROBOT_SHOOTING_ERROR_MARGIN_PX);
}

Direction Robot::getMovingDirection() const {
  // If the player cannot be shot, pick a direction to move in for closing the distance to the player.
  // The direction picked should be the longer of the two (horizontal or vertical), so that the overall distance to
  // the player decreases the most. Diagonal is chosen if they're equal.

  Vect2D us = this->getPosition();
  Vect2D them = this->_playerPositionProxy.getPlayerPosition();

  int xDistance = absval(us.x - them.x);
  Direction horizontal = (us.x < them.x) ? Direction::East() : Direction::West();

  int yDistance = absval(us.y - them.y);
  Direction vertical = (us.y < them.y) ? Direction::North() : Direction::South();

  if (xDistance == yDistance) {
    return horizontal + vertical;
  } else if (xDistance > yDistance) {
    return horizontal;
  } else {  // xDistance < yDistance
    return vertical;
  }
}

bool Robot::shouldAvoidWalls() const {
  switch (this->_avoidancePolicy) {
    case RobotWallAvoidancePolicy::ALWAYS:
      return true;
    case RobotWallAvoidancePolicy::SOMETIMES:
      return randInt(0, 1) == 1;
    case RobotWallAvoidancePolicy::NEVER:
      return false;
  }
}