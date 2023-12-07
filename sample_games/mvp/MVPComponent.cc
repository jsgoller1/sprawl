#include "MVPComponent.hh"

#include "Actor.hh"
#include "Math.hh"
#include "PhysicsComponent.hh"

void MVPComponent::onKeyDown(char key) {
  // Get the physics component
  std::shared_ptr<PhysicsComponent> physicsComponent = this->getOwner()->getComponent<PhysicsComponent>();
  // Add the force

  real xForce = this->xForceAdded * (key == 'd' ? 1 : -1);
  // real yForce = this->xForceAdded * (key == 'd' ? 1 : -1);

  physicsComponent->applyForce(Vect2D(xForce, real(0)));
  // physicsComponent->applyForce(Vect2D(xForce, yForce));
}
