#pragma once

#include "RealisticPhysicsComponent.hh"

/*
CharacterPhysicsComponent is a specialized version of PhysicsComponent
that has character-related physics functionality.
*/

class CharacterPhysicsComponent : public RealisticPhysicsComponent {
 public:
  CharacterPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity = nullptr);
  CharacterPhysicsComponent(const std::shared_ptr<RealisticPhysicsComponent> comp);
  ~CharacterPhysicsComponent() override;

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
