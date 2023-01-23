#include "Player.hh"

#include "Configs.hh"
#include "Direction.hh"
#include "InputHandler.hh"
#include "PlayerSpriteManager.hh"

#define PLAYER_DEFAULT_WIDTH 35
#define PLAYER_DEFAULT_HEIGHT 70

Player::Player(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy,
               DrawingProxy& drawingProxy, const PlayerSpriteManager& playerSpriteManager)
    : GameObject(position, velocity), IShooting(shootingProxy) {
  this->_playerAnimationSet = std::unique_ptr<PlayerAnimationSet>(new PlayerAnimationSet(playerSpriteManager));
  this->_drawingComponent = std::unique_ptr<AnimatedDrawingComponent>(
      new AnimatedDrawingComponent(this->getPositionComponent(), PLAYER_DEFAULT_HEIGHT, PLAYER_DEFAULT_WIDTH,
                                   drawingProxy, this->_playerAnimationSet->idle()));
  this->_state = CharacterState::IDLE;
  this->_sinceLastShot = 0;
  this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->idle());
}

AnimatedDrawingComponent& Player::getDrawingComponent() const { return *this->_drawingComponent; }

void Player::resolveCollision(GameObject& target) {
  (void)target;
  // TODO: I'd prefer we didn't do either state or animation setting here; both already have
  // respective update functions, and should be done there.
  // TODO: Maybe we should have an event queue of some kind and state updates process events on that queue?
  if (!(this->_state == CharacterState::DYING || this->_state == CharacterState::DEAD)) {
    this->_state = CharacterState::DYING;
    this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->dying());
  }
}

void Player::update(const InputHandler& inputHandler, const time_ms deltaT) {
  this->_state = this->getNewState(this->_state, inputHandler);
  if (this->_state == CharacterState::DEAD) {
    this->setPosition(Vect2D(-2000, -2000));
  }
  this->setVelocity(this->getNewVelocity(this->_state, inputHandler));
  this->updateAnimation(deltaT, inputHandler.getArrowKeyDirection(), this->_state);
  this->shootingBehavior(deltaT, inputHandler.getArrowKeyDirection());
  this->move();
}

CharacterState Player::getNewState(const CharacterState currentState, const InputHandler& inputHandler) const {
  if (currentState == CharacterState::DEAD) {
    return currentState;
  }

  if (currentState == CharacterState::DYING) {
    if (this->getDrawingComponent().getAnimationSequence().isComplete()) {
      return CharacterState::DEAD;
    }
    return currentState;
  }
  if (inputHandler.spacePressed() && inputHandler.movementKeysPressed()) {
    return CharacterState::SHOOTING;
  }
  if (inputHandler.movementKeysPressed()) {
    return CharacterState::MOVING;
  }
  return CharacterState::IDLE;
}

Vect2D Player::getNewVelocity(const CharacterState state, const InputHandler& inputHandler) const {
  if (state != CharacterState::MOVING) {
    return Vect2D::zero();
  }
  return Vect2D(inputHandler.getArrowKeyDirection()) * PLAYER_MOVE_SPEED;
}

void Player::updateAnimation(const time_ms deltaT, const Direction& movementDirection, const CharacterState state) {
  switch (state) {
    case CharacterState::IDLE:
      this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->idle());
      break;
    case CharacterState::MOVING:
      this->_drawingComponent->setAnimationSequence((movementDirection.getX() == 1)
                                                        ? this->_playerAnimationSet->movingE()
                                                        : this->_playerAnimationSet->movingW());
      break;
    case CharacterState::SHOOTING:
      this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->shooting(movementDirection));
      break;
    case CharacterState::DYING:
      this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->dying());
      break;
    case CharacterState::DEAD:
      this->_drawingComponent->setAnimationSequence(this->_playerAnimationSet->dead());
      break;
  }
  this->_drawingComponent->updateAnimationSequence(deltaT);
}

void Player::shootingBehavior(const time_ms deltaT, const Direction& shootingDirection) {
  this->_sinceLastShot += deltaT;
  if (this->_state == CharacterState::SHOOTING && this->_sinceLastShot > PLAYER_SHOOT_DELAY_MS) {
    this->_sinceLastShot = 0;
    // TODO: Having this constant offset is probably brittle; should calculate it
    // so that if the screen / sprite sizes ever change, it won't break.
    this->shoot(shootingDirection, this->getPosition(), GREEN);
  }
}
