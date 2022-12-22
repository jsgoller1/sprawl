#include "CharacterPhysicsComponent.hh"

#define CHARACTER_ENABLE_GRAVITY true
#define CHARACTER_ENABLE_FORCE_RESPONSIVE true
#define CHARACTER_MAX_SPEED 10.0

CharacterPhysicsComponent::~CharacterPhysicsComponent() = default;

CharacterPhysicsComponent::CharacterPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity)
    : RealisticPhysicsComponent(ownerIdentity, CHARACTER_ENABLE_GRAVITY, CHARACTER_ENABLE_FORCE_RESPONSIVE,
                                CHARACTER_MAX_SPEED) {}

CharacterPhysicsComponent::CharacterPhysicsComponent(const std::shared_ptr<RealisticPhysicsComponent> comp)
    : RealisticPhysicsComponent(*comp) {}

std::shared_ptr<CharacterPhysicsComponent> CharacterPhysicsComponent::getptr() {
  return std::static_pointer_cast<CharacterPhysicsComponent, Component>(this->shared_from_this());
}

void CharacterPhysicsComponent::applyJumpForce() {
  Vect2D moveForce = Vect2D(0.0, 10.0);
  this->applyForce(moveForce);
}

void CharacterPhysicsComponent::applyMovementForce(const Direction& direction) {
  PositionUnit speed = this->getMaxSpeed();
  speed *= (direction == Direction::Left()) ? -1.0 : 1.0;
  Vect2D moveForce = Vect2D(speed, 0.0);
  this->applyForce(moveForce);
}
bool CharacterPhysicsComponent::isMidair() { return false; }
