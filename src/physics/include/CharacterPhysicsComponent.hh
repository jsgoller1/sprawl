#pragma once

#include "PhysicsComponent.hh"

/*
CharacterPhysicsComponent is a specialized version of PhysicsComponent
that has character-related physics functionality.
*/

class CharacterPhysicsComponent : public PhysicsComponent {
 public:
  CharacterPhysicsComponent(
      const GameObjectNameSPtr ownerName,
      const shared_ptr<PositionComp> positionComp,
      const shared_ptr<BoundingBoxParams> boundingBoxParams = nullptr,
      const bool collisionsSetting = false, const bool gravitySetting = false);
  void applyJumpForce();
  void applyMovementForce(const shared_ptr<Direction> direction);
  void applyMovementForceOld(const shared_ptr<Direction> direction);

  // TODO: This hides the name PhysicsComponent::getptr(). This is probably
  // a footgun and I'm going to regret it later.
  // Ideas:
  // - define individual helper fns like getptr_CharacterPhysicsComponent()
  // which are friends to the class and can call shared_from_this() on them
  // - Create some kind of factory that can take a pointer to an object
  //   and return a shared pointer to it.
  shared_ptr<CharacterPhysicsComponent> getptr();

 private:
  real mass = 1.0;
};
