#pragma once
#include "Identity.hh"
#include "Manager.hh"

/*
 * Component implements the Component design pattern:
 * https://gameprogrammingpatterns.com/component.html
 * Components are used to manage specific behavior (physics, AI, drawing, etc),
 * and are composed with Entities to decouple those behaviors and make them
 * reusable. Component should not be used directly, but as a base class.
 * A Component should not know anything about the Entity that owns it,
 * except for its Identity and any references to its Entity's other components
 * (e.g., a PhysicsComponent implementing force-based movement will need to
 * interact with its owning Entity's PositionComponent). Components should not
 * interact with other Entities directly either; each Component should implement
 * methods that interact with other Components, which are then utilized by a
 * respective Manager class that handles interactions between Components (e.g.
 * PhysicsComponents has a checkCollision(otherComponent) method that
 * PhysicsManager would call against any other relevant PhysicsComponents).
 * Components may also be utlized by specialized classes (like Renderer) that
 * take a list of DrawingComponents who know information required to draw their
 * Entity on the screen.
 */

class Component : public enable_shared_from_this<Component> {
 public:
  Component(shared_ptr<const Identity> parentIdentity)
      : parentIdentity(parentIdentity){};
  shared_ptr<const Identity> getParentIdentity() {
    return this->parentIdentity;
  };

  // NOTE: C++ doesn't support overriding methods in parent classes with methods
  // in the child class that return a smart pointer to a covariant type; you can
  // only do this with raw pointers. The solution is to do the overriding with a
  // private method that returns a raw pointer to the covariant type, then call
  // that method from a public method that returns a smart pointer to it. The
  // public method should have the same name as the one in the parent class so
  // name hiding occurs. The compiler won't catch incorrectly named functions,
  // but there's no other simple way to do this.
  shared_ptr<Manager> getManager();
  void setManager(shared_ptr<Manager> manager);

 private:
  // Disallow creation of components with no parents
  Component() = delete;
  shared_ptr<const Identity> parentIdentity;

  virtual Manager* getManagerRaw() const = 0;
  virtual void getManagerRaw(Manager* manager) = 0;
};
