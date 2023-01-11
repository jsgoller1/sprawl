#include "Player.hh"

#include "Direction.hh"
#include "InputHandler.hh"
#include "PlayerSpriteManager.hh"

#define PLAYER_DEFAULT_HEIGHT 100
#define PLAYER_DEFAULT_WIDTH 30

Vect2D getBulletPositionOffset(const Vect2D& shooterPosition) {
  (void)shooterPosition;
  return Vect2D::zero();
}

Player::Player(const Vect2D& position, const Vect2D& velocity, ShootingProxy& shootingProxy, DrawingProxy& drawingProxy,
               const PlayerSpriteManager& playerSpriteManager)
    : GameObject(position, velocity), IShooting(shootingProxy) {
  this->_drawingComponent = std::unique_ptr<AnimatedDrawingComponent>(new AnimatedDrawingComponent(
      this->getPositionComponent(), PLAYER_DEFAULT_HEIGHT, PLAYER_DEFAULT_WIDTH, drawingProxy, nullptr));
  this->_state = IDLE;
  this->_playerAnimationSet = std::unique_ptr<PlayerAnimationSet>(new PlayerAnimationSet(playerSpriteManager));
  this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->getIdleSequence());
}

AnimatedDrawingComponent& Player::getDrawingComponent() const { return *this->_drawingComponent; }

void Player::resolveCollision(GameObject& target) {
  (void)target;
  // TODO: I'd prefer we didn't do either state or animation setting here; both already have
  // respective update functions, and should be done there.
  if (this->_state != DYING) {
    this->_state = DYING;
    this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->getDyingSequence());
  }
}

void Player::update(const InputHandler& inputHandler, const time_ms deltaT) {
  PlayerState nextState = this->updateState(this->_state, inputHandler);
  Vect2D newVelocity = this->updateVelocity(nextState, inputHandler);

  this->updateAnimation(deltaT, Direction(newVelocity), this->_state, nextState);
  this->setVelocity(newVelocity);
  this->_state = nextState;
  if (this->_state == SHOOTING) {
    this->shoot(inputHandler.getArrowKeyDirection(), getBulletPositionOffset(this->getPosition()));
  }
  this->move();
}

PlayerState Player::updateState(const PlayerState currentState, const InputHandler& inputHandler) const {
  switch (currentState) {
    case IDLE:
      if (inputHandler.lCtrlPressed()) {
        return SHOOTING;
      }
      if (inputHandler.movementKeysPressed()) {
        return MOVING;
      }
      return IDLE;
    case MOVING:
      if (inputHandler.lCtrlPressed()) {
        return SHOOTING;
      }
      if (!inputHandler.movementKeysPressed()) {
        return IDLE;
      }
      return MOVING;
    case SHOOTING:
      if (!inputHandler.movementKeysPressed() && !inputHandler.lCtrlPressed()) {
        return IDLE;
      }
      if (inputHandler.movementKeysPressed() && !inputHandler.lCtrlPressed()) {
        return MOVING;
      }
      return SHOOTING;
    case DYING:
      return DYING;
  }
  // TODO: This should not be necessary, but the compiler requires all paths to return a value.
}

Vect2D Player::updateVelocity(const PlayerState state, const InputHandler& inputHandler) const {
  if (state != MOVING) {
    return Vect2D::zero();
  }

  Vect2D newVelocity = this->getVelocity();

  // Determine x-axis velocity
  if (inputHandler.bothHorizontalKeysPressed()) {
    newVelocity.x = 0;
  } else if (inputHandler.leftArrowPressed()) {
    newVelocity.x = -PLAYER_MOVE_SPEED;
  } else if (inputHandler.rightArrowPressed()) {
    newVelocity.x = PLAYER_MOVE_SPEED;
  } else {
    newVelocity.x = 0;
  }

  // Determine y-axis velocity
  if (inputHandler.bothVerticalKeysPressed()) {
    newVelocity.y = 0;
  } else if (inputHandler.downArrowPressed()) {
    newVelocity.y = -PLAYER_MOVE_SPEED;
  } else if (inputHandler.upArrowPressed()) {
    newVelocity.y = PLAYER_MOVE_SPEED;
  } else {
    newVelocity.y = 0;
  }

  return newVelocity;
}

void Player::updateAnimation(const time_ms deltaT, const Direction& movementDirection, const PlayerState oldState,
                             const PlayerState newState) {
  if (oldState == newState) {
    // No state change occurred, so just advance the current animation sequence
    this->_drawingComponent->updateAnimationSequence(deltaT);
    return;
  }

  switch (newState) {
    case IDLE:
      this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->getIdleSequence());
      break;
    case MOVING:
      this->_drawingComponent->setAnimationSequence((movementDirection.getX() == 1)
                                                        ? this->_playerAnimationSet->getMovingESequence()
                                                        : this->_playerAnimationSet->getMovingWSequence());
      break;
    case SHOOTING:
      this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->getShootingSequence(movementDirection));
      break;
    case DYING:
      this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->getDyingSequence());
      break;
  }
}
