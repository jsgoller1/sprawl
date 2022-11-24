#include "SimplePhysicsComponent.hh"

SimplePhysicsComponent::SimplePhysicsComponent(const std::shared_ptr<Identity> ownerIdentity,
                                               const PositionUnit maxSpeed, const PositionUnit minSpeed,
                                               const Vect2D velocity)
    : PhysicsComponent(ownerIdentity, maxSpeed, minSpeed, velocity) {}

SimplePhysicsComponent::~SimplePhysicsComponent() = default;

void SimplePhysicsComponent::resolveCollision(const Collision& collision) {
  LOG_DEBUG_SYS(PHYSICS, "Collision occurred (simple component source): {} -> {}", *collision.source()->getEntityID(),
                *collision.target()->getEntityID());
}

Vect2D SimplePhysicsComponent::integrate(const time_ms duration) { return this->getVelocity() * duration; }
