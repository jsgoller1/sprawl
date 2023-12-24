#include "MVPComponent.hh"

#include "Actor.hh"
#include "Input.hh"
#include "Math.hh"
#include "PhysicsComponent.hh"
#include "SystemProxy.hh"

void MVPComponent::moveLeft(PhysicsComponent& physicsComponent) {
  physicsComponent.applyForce(Vect2D(-this->forceAdded, real(0)));
}

void MVPComponent::moveRight(PhysicsComponent& physicsComponent) {
  physicsComponent.applyForce(Vect2D(this->forceAdded, real(0)));
}

void MVPComponent::onGameLoop() {
  Input input = Input();
  // Get the physics component
  std::shared_ptr<PhysicsComponent> physicsComponent = this->getOwner()->getComponent<PhysicsComponent>();
  if (input.getKey(SDLK_LEFT)) {
    this->moveLeft(*physicsComponent);
  } else if (input.getKey(SDLK_RIGHT)) {
    this->moveRight(*physicsComponent);
  } else if (input.getKey(SDLK_ESCAPE)) {
    SystemProxy::instance().quit();
  }
}
