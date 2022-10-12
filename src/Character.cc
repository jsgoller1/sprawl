#include "Character.hh"

Character::Character(
    const shared_ptr<EntityName> entityName,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent,
    const shared_ptr<CharacterPhysicsComponent> characterPhysicsComponent,
    const shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, collisionDetectionComponent,
                 nullptr, drawingComponent) {
  this->moveSpeed = shared_ptr<Vect2D>(new Vect2D(10.0, 10.0));
  this->characterPhysicsComponent =
      (characterPhysicsComponent == nullptr)
          ? shared_ptr<CharacterPhysicsComponent>(new CharacterPhysicsComponent(
                this->getIdentity(), this->getPositionComponent(),
                this->getCollisionDetectionComponent()))
          : characterPhysicsComponent;
  this->getPhysicsComponent()->setGravityEnabled(true);
}

shared_ptr<CharacterPhysicsComponent> Character::getPhysicsComponent() const {
  return this->getPhysicsComponent_impl()->getptr();
}
void Character::setPhysicsComponent(
    const shared_ptr<CharacterPhysicsComponent> physicsComponent) {
  this->setPhysicsComponent_impl(physicsComponent.get());
}

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.
  shared_ptr<Vect2D> newVelocity = this->getPhysicsComponent()->getVelocity();

  switch (action) {
    case MOVE_UP:
      // TODO: Jumping / double jumping
      break;
    case MOVE_LEFT:
      this->getPhysicsComponent()->applyMovementForce(Direction::Left());
      break;
    case MOVE_RIGHT:
      this->getPhysicsComponent()->applyMovementForce(Direction::Right());
      break;
    case STOP_MOVE_RIGHT:
    case STOP_MOVE_LEFT:
      newVelocity->x = 0;
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
  this->characterPhysicsComponent = shared_ptr<CharacterPhysicsComponent>(
      new CharacterPhysicsComponent(comp->getptr()));
}
CharacterPhysicsComponent* Character::getPhysicsComponent_impl() const {
  return this->characterPhysicsComponent.get();
}
