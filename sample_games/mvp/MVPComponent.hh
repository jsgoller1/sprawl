#pragma once

#include "LoadableBehaviorComponent.hh"
#include "Math.hh"

// fwd decls
class PhysicsComponent;

class MVPComponent : public LoadableBehaviorComponent<MVPComponent> {
 public:
  MVPComponent() : LoadableBehaviorComponent<MVPComponent>() {}
  ~MVPComponent() override = default;

  BIND(real, forceAdded, MVPComponent)

  // We'll add the force in this function
  void onGameLoop() override;

 private:
  void moveLeft(PhysicsComponent& physicsComponent);
  void moveRight(PhysicsComponent& physicsComponent);
};
REGISTER_COMPONENT(MVPComponent);
