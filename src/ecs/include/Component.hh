#pragma once
#include "Identity.hh"

/*
 * Component implements the Component design pattern:
 * https://gameprogrammingpatterns.com/component.html
 * Components are used to manage specific behavior (physics, AI, drawing, etc),
 * and are composed with Entities to decouple those behaviors and make them
 * reusable. Component should not be used directly, but as a base class.
 * Components should not know anything about their Entities that own them,
 * except for its Identity and any references to its Entity's other components
 * (e.g., a PhysicsComponent implementing force-based movement will need to
 * interact with its owning Entity's PositionComponent). Components should not
 * interact with other Entities directly either; each Component should implement
 * methods that interact with other Components, which are then utilized by a
 * respective Manager class that handles interactions between Components (e.g.
 * PhysicsComponents has a checkCollision(otherComponent) method that
 * PhysicsManager would call against any other relevant PhysicsComponents).
 */

class Component {
 public:
  Component(shared_ptr<const Identity> parentIdentity)
      : parentIdentity(parentIdentity){};
  shared_ptr<const Identity> getParentIdentity() {
    return this->parentIdentity;
  };
  virtual shared_ptr<Manager> getManager() = 0;

 private:
  // Disallow creation of components with no parents
  Component() = delete;
  shared_ptr<const Identity> parentIdentity;
};
