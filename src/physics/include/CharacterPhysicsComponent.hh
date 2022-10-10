#pragma once

#include "Memory.hh"
#include "PhysicsComponent.hh"

#define ENABLE_GRAVITY true
#define ENABLE_FORCE_RESPONSIVE true

/*
CharacterPhysicsComponent is a specialized version of PhysicsComponent
that has character-related physics functionality.
*/

class CharacterPhysicsComponent : public PhysicsComponent {
 public:
  CharacterPhysicsComponent(
      const shared_ptr<Identity> ownerIdentity,
      const shared_ptr<PositionComponent> positionComponent,
      const shared_ptr<CollisionDetectionComponent>
          collisionDetectionComponent);
  CharacterPhysicsComponent(const shared_ptr<PhysicsComponent> comp);

  // TODO: This hides the name PhysicsComponent::getptr(). This is probably
  // a footgun and I'm going to regret it later.
  // Ideas:
  // - define individual helper fns like getptr_CharacterPhysicsComponent()
  // which are friends to the class and can call shared_from_this() on them
  // - Create some kind of factory that can take a pointer to an object
  //   and return a shared pointer to it.
  shared_ptr<CharacterPhysicsComponent> getptr();

  void applyJumpForce();
  void applyMovementForce(const shared_ptr<Direction> direction);
  bool isMidair();
};
