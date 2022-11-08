#pragma once

#include "PhysicsComponent.hh"

#define ENABLE_GRAVITY true
#define ENABLE_FORCE_RESPONSIVE true

/*
CharacterPhysicsComponent is a specialized version of PhysicsComponent
that has character-related physics functionality.
*/

class CharacterPhysicsComponent : public PhysicsComponent {
 public:
  CharacterPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity);
  CharacterPhysicsComponent(const std::shared_ptr<PhysicsComponent> comp);

  // TODO: This hides the name PhysicsComponent::getptr(). This is probably
  // a footgun and I'm going to regret it later.
  // Ideas:
  // - define individual helper fns like getptr_CharacterPhysicsComponent()
  // which are friends to the class and can call shared_from_this() on them
  // - Create some kind of factory that can take a pointer to an object
  //   and return a shared pointer to it.
  std::shared_ptr<CharacterPhysicsComponent> getptr();

  void applyJumpForce();
  void applyMovementForce(const Direction& direction);
  bool isMidair();
};
