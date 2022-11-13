#include "CharacterPhysicsComponent.hh"

CharacterPhysicsComponent::CharacterPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity)
    : PhysicsComponent(ownerIdentity, ENABLE_GRAVITY, ENABLE_FORCE_RESPONSIVE) {
  this->maxSpeed(10.0);
}

CharacterPhysicsComponent::CharacterPhysicsComponent(const std::shared_ptr<PhysicsComponent> comp)
    : PhysicsComponent(*comp) {}

std::shared_ptr<CharacterPhysicsComponent> CharacterPhysicsComponent::getptr() {
  return std::static_pointer_cast<CharacterPhysicsComponent, Component>(this->shared_from_this());
}

void CharacterPhysicsComponent::applyJumpForce() {
  Vect2D moveForce = Vect2D(0.0, 10.0);
  this->applyForce(moveForce);
}

void CharacterPhysicsComponent::applyMovementForce(const Direction& direction) {
  PositionUnit speed = this->maxSpeed();
  speed *= (direction == Direction::Left()) ? -1.0 : 1.0;
  Vect2D moveForce = Vect2D(speed, 0.0);
  this->applyForce(moveForce);
}
bool CharacterPhysicsComponent::isMidair() { return false; }
