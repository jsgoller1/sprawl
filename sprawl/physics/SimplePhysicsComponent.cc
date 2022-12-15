#include "SimplePhysicsComponent.hh"

SimplePhysicsComponent::SimplePhysicsComponent(const std::shared_ptr<Identity> ownerIdentity,
                                               const PositionUnit maxSpeed, const PositionUnit minSpeed,
                                               const Vect2D velocity)
    : PhysicsComponent(ownerIdentity, maxSpeed, minSpeed, velocity) {}

SimplePhysicsComponent::~SimplePhysicsComponent() = default;

Vect2D SimplePhysicsComponent::integrate(const time_ms duration) { return this->getVelocity() * duration; }

void SimplePhysicsComponent::resolveCollision(const Collision& collision) {
  // We don't need to do anything with the collision for the simple scenario;
  // just stop moving.
  (void)collision;
  this->setVelocity(Vect2D::zero());
}
