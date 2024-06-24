#include "Character.hh"

Character::Character(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
                     const std::shared_ptr<CollisionComponent> collisionComponent,
                     const std::shared_ptr<CharacterPhysicsComponent> physicsComponent,
                     const std::shared_ptr<GraphicsComponent2D> graphicsComponent2D)
    : GameObject(entityName, positionComponent, collisionComponent, nullptr, graphicsComponent2D) {
  this->_physicsComponent = physicsComponent;
  this->_physicsComponent->setOwnerIdentity(this->getIdentity().shared_from_this());
}

CharacterPhysicsComponent& Character::getPhysicsComponent() const { return *this->_physicsComponent; }

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.

  switch (action) {
    case MOVE_UP:
      this->jump();
      break;
    case MOVE_LEFT:
      this->getPhysicsComponent().applyMovementForce(Direction::Left());
      break;
    case MOVE_RIGHT:
      this->getPhysicsComponent().applyMovementForce(Direction::Right());
      break;
    default:
      // TODO: should warn
      break;
  }
}

void Character::jump() {
  if (not this->canDoubleJump) {
    return;
  }
  if (this->getPhysicsComponent().isMidair()) {
    this->canDoubleJump = false;
  }
  this->getPhysicsComponent().applyJumpForce();
}
