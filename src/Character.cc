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
void Character::setPhysicsComponent(const std::shared_ptr<CharacterPhysicsComponent> physicsComponent) {
  this->setPhysicsComponent_impl(physicsComponent.get());
}

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.
  Vect2D newVelocity = this->getPhysicsComponent()->velocity();

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
    case STOP_MOVE_RIGHT:
    case STOP_MOVE_LEFT:
      newVelocity.x(0);
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

// Private
void Character::setPhysicsComponent_impl(PhysicsComponent* const comp) {
  this->characterPhysicsComponent =
      std::shared_ptr<CharacterPhysicsComponent>(new CharacterPhysicsComponent(comp->getptr()));
}
CharacterPhysicsComponent* Character::getPhysicsComponent_impl() const { return this->characterPhysicsComponent.get(); }
