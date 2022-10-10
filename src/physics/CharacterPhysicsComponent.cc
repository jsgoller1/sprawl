#include "CharacterPhysicsComponent.hh"

CharacterPhysicsComponent::CharacterPhysicsComponent(
    const shared_ptr<Identity> ownerIdentity,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent)
    : PhysicsComponent(ownerIdentity, positionComponent,
                       collisionDetectionComponent, ENABLE_GRAVITY,
                       ENABLE_FORCE_RESPONSIVE) {}

CharacterPhysicsComponent::CharacterPhysicsComponent(
    const shared_ptr<PhysicsComponent> comp)
    : PhysicsComponent(comp->getOwnerIdentity(), comp->getPositionComponent(),
                       comp->getCollisionDetectionComponent(), ENABLE_GRAVITY,
                       ENABLE_FORCE_RESPONSIVE) {}

shared_ptr<CharacterPhysicsComponent> CharacterPhysicsComponent::getptr() {
  return static_pointer_cast<CharacterPhysicsComponent, PhysicsComponent>(
      this->shared_from_this());
}

void CharacterPhysicsComponent::applyJumpForce() {}
void CharacterPhysicsComponent::applyMovementForce(
    const shared_ptr<Direction> direction) {
  PositionUnit speed = this->getMaxSpeed();
  speed *= (*direction == *Direction::Left()) ? -1.0 : 1.0;
  shared_ptr<Vect2D> moveForce = shared_ptr<Vect2D>(new Vect2D(speed, 0.0));
  this->applyForce(moveForce);
}
bool CharacterPhysicsComponent::isMidair() { return false; }
