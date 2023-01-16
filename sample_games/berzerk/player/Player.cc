#include "Player.hh"

#include "Direction.hh"
#include "InputHandler.hh"
#include "PlayerSpriteManager.hh"

#define PLAYER_DEFAULT_HEIGHT 100
#define PLAYER_DEFAULT_WIDTH 30

constexpr int PLAYER_SHOOT_DELAY_MS = 750;

Vect2D getBulletPositionOffset(const Vect2D& shooterPosition) { return shooterPosition; }

Player::Player(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy,
               DrawingProxy& drawingProxy, const PlayerSpriteManager& playerSpriteManager)
    : GameObject(position, velocity), IShooting(shootingProxy) {
  this->_drawingComponent = std::unique_ptr<AnimatedDrawingComponent>(new AnimatedDrawingComponent(
      this->getPositionComponent(), PLAYER_DEFAULT_HEIGHT, PLAYER_DEFAULT_WIDTH, drawingProxy, nullptr));
  this->_state = IDLE;
  this->_sinceLastShot = 0;
  this->_playerAnimationSet = std::unique_ptr<PlayerAnimationSet>(new PlayerAnimationSet(playerSpriteManager));
  this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->getIdleSequence());
}

AnimatedDrawingComponent& Player::getDrawingComponent() const { return *this->_drawingComponent; }

void Player::resolveCollision(GameObject& target) {
  (void)target;
  // TODO: I'd prefer we didn't do either state or animation setting here; both already have
  // respective update functions, and should be done there.
  // TODO: Maybe we should have an event queue of some kind and state updates process events on that queue?
  if (this->_state != DYING) {
    this->_state = DYING;
    this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->getDyingSequence());
  }
}

void Player::update(const InputHandler& inputHandler, const time_ms deltaT) {
  this->_state = this->getNewState(this->_state, inputHandler);
  this->setVelocity(this->getNewVelocity(this->_state, inputHandler));
  this->updateAnimation(deltaT, inputHandler.getArrowKeyDirection(), this->_state);

  // TODO: Shooting should be its own function since it involves a delay
  this->_sinceLastShot += deltaT;
  if (this->_state == SHOOTING && this->_sinceLastShot > PLAYER_SHOOT_DELAY_MS) {
    this->_sinceLastShot = 0;
    this->shoot(inputHandler.getArrowKeyDirection(), getBulletPositionOffset(this->getPosition()), GREEN);
  }
  this->move();
}

PlayerState Player::getNewState(const PlayerState currentState, const InputHandler& inputHandler) const {
  if (currentState == DYING) {
    return DYING;
  }
  if (inputHandler.spacePressed() && inputHandler.movementKeysPressed()) {
    return SHOOTING;
  }
  if (inputHandler.movementKeysPressed()) {
    return MOVING;
  }
  return IDLE;
}

Vect2D Player::getNewVelocity(const PlayerState state, const InputHandler& inputHandler) const {
  if (state != MOVING) {
    return Vect2D::zero();
  }
  return Vect2D(inputHandler.getArrowKeyDirection()) * PLAYER_MOVE_SPEED;
}

void Player::updateAnimation(const time_ms deltaT, const Direction& movementDirection, const PlayerState state) {
  switch (state) {
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
  this->_drawingComponent->updateAnimationSequence(deltaT);
}
