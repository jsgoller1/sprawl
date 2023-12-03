#include "MVPComponent.hh"

#include "Actor.hh"
#include "Math.hh"
#include "PhysicsComponent.hh"

void MVPComponent::onLoop() {
  // Get the physics component
  std::shared_ptr<PhysicsComponent> physicsComponent = this->getOwner()->getComponent<PhysicsComponent>();
  // Add the force
  physicsComponent->applyForce(Vect2D(real(0), forceAdded));
}
