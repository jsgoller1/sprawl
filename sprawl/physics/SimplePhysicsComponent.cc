#include "SimplePhysicsComponent.hh"

SimplePhysicsComponent::SimplePhysicsComponent(const std::shared_ptr<Identity> ownerIdentity,
                                               const PositionUnit maxSpeed, const PositionUnit minSpeed,
                                               const Vect2D velocity)
    : PhysicsComponent(ownerIdentity, maxSpeed, minSpeed, velocity) {}

SimplePhysicsComponent::~SimplePhysicsComponent() = default;

Vect2D SimplePhysicsComponent::integrate(const time_ms duration) { return this->getVelocity() * duration; }
