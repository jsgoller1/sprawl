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

template <typename DerivedComponent>
class Component : public enable_shared_from_this<Component<DerivedComponent>> {
 public:
  std::shared_ptr<Component<DerivedComponent>> getptr() {
    return this->shared_from_this();
  }

  Component(shared_ptr<const Identity> parentIdentity)
      : parentIdentity(parentIdentity){};
  shared_ptr<const Identity> getParentIdentity() {
    return this->parentIdentity;
  };

  template <typename DerivedManager>
  shared_ptr<Manager<DerivedManager>> getManager() {
    return this->getManagerRaw()->getptr();
  }

  template <typename DerivedManager>
  void setManager(shared_ptr<Manager<DerivedManager>> manager) {
    this->setManagerRaw(manager.get());
  }

 private:
  // Disallow creation of components with no parents
  Component<DerivedComponent>() = delete;
  shared_ptr<const Identity> parentIdentity;

  template <typename DerivedManager>
  static shared_ptr<Manager<DerivedManager>> manager = nullptr;

  template <typename DerivedManager>
  Manager<DerivedManager>* getManagerRaw() {
    return this->manager->get();
  }

  template <typename DerivedManager>
  void setManagerRaw(Manager<DerivedManager>* manager) {
    this->manager = manager->getptr();
  }
};
