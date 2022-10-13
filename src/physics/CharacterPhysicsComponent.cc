#include "CharacterPhysicsComponent.hh"

CharacterPhysicsComponent::CharacterPhysicsComponent(
    const shared_ptr<Identity> ownerIdentity,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionComponent> collisionComponent)
    : PhysicsComponent(ownerIdentity, positionComponent, collisionComponent,
                       ENABLE_GRAVITY, ENABLE_FORCE_RESPONSIVE) {
  this->setMaxSpeed(10.0);
}

CharacterPhysicsComponent::CharacterPhysicsComponent(
    const shared_ptr<PhysicsComponent> comp)
    : PhysicsComponent(comp->getOwnerIdentity(), comp->getPositionComponent(),
                       comp->getCollisionComponent(), ENABLE_GRAVITY,
                       ENABLE_FORCE_RESPONSIVE) {}

shared_ptr<CharacterPhysicsComponent> CharacterPhysicsComponent::getptr() {
  return static_pointer_cast<CharacterPhysicsComponent, Component>(
      this->shared_from_this());
}

void CharacterPhysicsComponent::applyJumpForce() {
  shared_ptr<Vect2D> moveForce = shared_ptr<Vect2D>(new Vect2D(0.0, -10.0));
  this->applyForce(moveForce);
}

void CharacterPhysicsComponent::applyMovementForce(
    const shared_ptr<Direction> direction) {
  PositionUnit speed = this->getMaxSpeed();
  speed *= (*direction == *Direction::Left()) ? -1.0 : 1.0;
  shared_ptr<Vect2D> moveForce = shared_ptr<Vect2D>(new Vect2D(speed, 0.0));
  this->applyForce(moveForce);
}
bool CharacterPhysicsComponent::isMidair() { return false; }
