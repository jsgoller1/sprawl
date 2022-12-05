#include "Character.hh"

Character::Character(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
                     const std::shared_ptr<CollisionComponent> collisionComponent,
                     const std::shared_ptr<CharacterPhysicsComponent> characterPhysicsComponent,
                     const std::shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, collisionComponent, nullptr, drawingComponent) {
  this->moveSpeed = std::shared_ptr<Vect2D>(new Vect2D(10.0, 10.0));
  this->characterPhysicsComponent =
      (characterPhysicsComponent == nullptr)
          ? std::shared_ptr<CharacterPhysicsComponent>(new CharacterPhysicsComponent(this->getIdentity()))
          : characterPhysicsComponent;
  this->characterPhysicsComponent->setOwnerIdentity(this->getIdentity());
}

std::shared_ptr<CharacterPhysicsComponent> Character::getPhysicsComponent() const {
  return this->getPhysicsComponent_impl()->getptr();
}

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.

  switch (action) {
    case MOVE_UP:
      this->jump();
      break;
    case MOVE_LEFT:
      this->getPhysicsComponent()->applyMovementForce(Direction::Left());
      break;
    case MOVE_RIGHT:
      this->getPhysicsComponent()->applyMovementForce(Direction::Right());
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
  if (this->getPhysicsComponent()->isMidair()) {
    this->canDoubleJump = false;
  }
  this->getPhysicsComponent()->applyJumpForce();
}

CharacterPhysicsComponent* Character::getPhysicsComponent_impl() const { return this->characterPhysicsComponent.get(); }
