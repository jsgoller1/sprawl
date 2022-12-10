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
  CharacterPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity = nullptr);
  CharacterPhysicsComponent(const std::shared_ptr<PhysicsComponent> comp);

  void applyJumpForce();
  void applyMovementForce(const Direction& direction);
  bool isMidair();
};
