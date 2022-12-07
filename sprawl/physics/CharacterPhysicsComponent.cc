#include "CharacterPhysicsComponent.hh"

CharacterPhysicsComponent::~CharacterPhysicsComponent() = default;

CharacterPhysicsComponent::CharacterPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity,
                                                     const bool forceResponsiveSetting, const bool gravitySetting,
                                                     const DragType dragType, const real dragCoefficient,
                                                     const PositionUnit maxSpeed, const PositionUnit minSpeed,
                                                     Vect2D velocity)
    : RealisticPhysicsComponent(ownerIdentity, forceResponsiveSetting, gravitySetting, dragType, dragCoefficient,
                                maxSpeed, minSpeed, velocity) {}

CharacterPhysicsComponent::CharacterPhysicsComponent(const std::shared_ptr<RealisticPhysicsComponent> comp)
    : RealisticPhysicsComponent(*comp) {}

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
