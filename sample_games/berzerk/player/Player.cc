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
    : GameObject(position, velocity),
      IShooting(shootingProxy),
      IAnimatedDrawing(this->getPositionComponent(), PLAYER_DEFAULT_HEIGHT, PLAYER_DEFAULT_WIDTH, drawingProxy,
                       nullptr) {
  this->_playerAnimationSet = std::unique_ptr<PlayerAnimationSet>(new PlayerAnimationSet(playerSpriteManager));
  this->setAnimationSequence(this->_playerAnimationSet->getIdleSequence());
}

void Player::resolveCollision(GameObject& target) { (void)target; }

void Player::update(const InputHandler& inputHandler) {
  PlayerState nextState = this->updateState(this->_state, inputHandler);
  Vect2D newVelocity = this->updateVelocity(this->_state, inputHandler);

  this->updateAnimation(this->_state, nextState, newVelocity);
  this->setVelocity(newVelocity);
  this->_state = nextState;
  if (this->_state == SHOOTING) {
    this->shoot(inputHandler.getArrowKeyDirection(), getBulletPositionOffset(this->getPosition()));
  }
}

PlayerState Player::updateState(const PlayerState currentState, const InputHandler& inputHandler) const {
  // TODO: This is just a hack for now to test the death animation until we have wall collisions working
  if (this->getPosition().y < -150) {
    return DYING;
  }

  switch (currentState) {
    case IDLE:
      if (inputHandler.lCtrlPressed()) {
        return SHOOTING;
      }
      if (inputHandler.movementKeysPressed()) {
        return MOVING;
      }
      break;
    case MOVING:
      if (inputHandler.lCtrlPressed()) {
        return SHOOTING;
      }
      if (!inputHandler.movementKeysPressed()) {
        return IDLE;
      }
      break;
    case SHOOTING:
      if (!inputHandler.movementKeysPressed() && !inputHandler.lCtrlPressed()) {
        return IDLE;
      }
      if (inputHandler.movementKeysPressed() && !inputHandler.lCtrlPressed()) {
        return MOVING;
      }
      break;
    case DYING:
      return DYING;
  }
  // TODO: This should not be necessary, but the compiler requires all paths to return a value.
  return IDLE;
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

void Player::updateAnimation(const PlayerState oldState, const PlayerState newState, const Vect2D& newVelocity) {
  // TODO: Why did we need newVelocity here? Did we just need the direction? Can we remove this parameter?
  (void)newVelocity;

  if (oldState == newState) {
    // No state change occurred, so just advance the current animation sequence
    this->updateAnimationSequence();
    return;
  }

  switch (newState) {
    case IDLE:
      this->setAnimationSequence(this->_playerAnimationSet->getIdleSequence());
      break;
    case MOVING:
      break;
    case SHOOTING:
      break;
    case DYING:
      this->setAnimationSequence(this->_playerAnimationSet->getDyingSequence());
      break;
  }
}
